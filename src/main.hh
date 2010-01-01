// -*- mode: c++; tab-width: 4; -*-
//
// Programa: autoproyecto Copyright (c) 2006 SISDETEC
// Author: Manuel Cano Muñoz
// Date: Mon Jan 23 21:58:12 2006
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
//   02110-1301	USA
//

//
// Includes
//
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

#define ADD_CONFIGURE(x,y) ::sprintf (_buf, x, _name.c_str(), \
	_version.c_str(), \
	_mail.c_str());	\
	y.addText (_buf);

#define ADD_PROYECT(x,y) ::sprintf (_buf, x, \
	_name.c_str(), \
	_name.c_str(), \
	_name.c_str());	\
	y.addText (_buf);
const char * CONFIGURE_GNOME_AC = NULL;
const char * CONFIGURE_AC = 
	"dnl Standard configure.ac\n"				\
	"AC_PREREQ(2.53)\n"							\
	"AC_INIT([%s], [%s], [%s])\n"				\
	"AC_CONFIG_AUX_DIR([build-aux])\n"			\
	"AM_INIT_AUTOMAKE([dist-bzip2])\n"						\
	"AM_CONFIG_HEADER([config.h:config.in])\n"	\
	"AC_CONFIG_SRCDIR([src/main.cc])\n"			\
	"\n"										\
	"dnl Checks for programs.\n"				\
	"AC_PROG_CXX\n"								\
	"dnl AC_PROG_CC\n"							\
	"dnl AC_PROG_LIBTOOL\n"						\
	"\n"										\
	"dnl Checks for libraries.\n"				\
	"\n"										\
	"dnl Checks for header files.\n"			\
	"dnl AC_HEADER_STDC\n"												\
	"dnl AC_CHECK_HEADERS([sys/types.h sys/socket.h stdlib.h unistd.h])\n" \
	"\n"																\
	"dnl Checks for typedefs, structures, and compiler characteristics.\n" \
	"dnl AC_ARG_WITH([categoria],\n"									\
	"dnl\n"																\
	"dnl \tAC_HELP_STRING([--with-categoria=CAT],\n"					\
	"dnl \t[Definir categoria de log]),\n"								\
	"dnl \t[categoria=$withval], [LOG_CATEGORIA=DEBUG])\n"				\
	"\n"																\
	"dnl if test \"$categoria\" != \"\"; then\n"						\
	"dnl \tCXXFLAGS=\"$CXXFLAGS -DLOG_CATEGORIA=\\\\\"$categoria\\\\\"\"\n" \
	"dnl fi\n"															\
	"\n"																\
	"\n"																\
	"dnl AM_CONDITIONAL(FEATURE, [test x\"$the_feature\" != x])"		\
	"dnl AC_DEFUN(AC_MSG_SUMMARY, [echo $1])\n"							\
	"dnl AC_DEFUN(WITH,"												\
	"dnl [\n"															\
	"dnl if test ${2_FALSE} ; then\n"									\
	"dnl \techo $1: enabled\n"											\
	"dnl else\n"														\
	"dnl \techo $1: disabled\n"											\
	"dnl fi\n"															\
	"dnl ])\n"															\
	"dnl\n"																\
	"dnl AC_MSG_SUMMARY(------------------)\n"							\
	"dnl AC_MSG_SUMMARY(  FEATURES:)\n"									\
	"dnl AC_MSG_SUMMARY(------------------)\n"							\
	"dnl WITH(feature, FEATURE)\n"										\
	"dnl AC_MSG_SUMMARY(------------------)\n"							\
	"dnl\n"																\
	"dnl Checks for library functions.\n"								\
	"\n"																\
	"dnl AC_SUBST(CFLAGS)\n"											\
	"dnl AC_SUBST(CPPFLAGS)\n"											\
	"dnl AC_SUBST(LDFLAGS)\n"											\
	"CFLAGS=\"-Wall -g $CFLAGS\n"										\
	"\n"																\
	"AC_CONFIG_FILES([Makefile src/Makefile])\n"						\
	"AC_OUTPUT\n";

const char * AUTORECONF = 
"# !/bin/bash\n"
"aclocal\n"
"autoheader\n"
"autoconf\n"
"autoheader\n"
"automake -c --add-missing\n";

const char * MAKEFILE_AM = "SUBDIRS = src\n";
const char * SRC_MAKEFILE_AM = 
"INCLUDES = -DG_LOG_DOMAIN=\\\"%s\\\"\n" \
"\t-I$(top_srcdir)\n" \
"\t$(GNOME_CFLAGS)\n" \
"\n" \
"LIBS = $(GNOME_LIBS)\n" \
"\n" \
"bin_PROGRAMS = %s\n" \
"%s_SOURCES = main.hh main.cc\n";

void use ();
void makeBody (std::string name, std::string author);

class file
{
public:
  file (std::string name, bool dir = false)
	:	_name (name),
		_dir (dir)
	{}
  file (const file & a) : _name (a._name) {}
  virtual ~file () {}
  file & operator = (const file & a)
	{
	  _name = a._name;
	  return *this;
	}
  std::string name () { return _name; }
  bool create ()
	{
	  if (_dir)
	  {
		return (::mkdir(_name.c_str(), 
						S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != -1);
	  }
	  else
	  {
		return (::creat(_name.c_str(), 
						S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH 
						| S_IROTH) != -1);
	  }
	}
  bool makeExecutable ()
	{
	  return (::chmod(_name.c_str(), S_IXUSR | S_IRUSR | S_IWUSR 
					  | S_IRGRP | S_IWGRP | S_IROTH | S_IROTH) != -1);
	}
  virtual bool addText (const char * text)
	{
	  FILE * f = ::fopen(_name.c_str(), "w");
	  if (! f)
	  {
		return false;
	  }
		
	  size_t len = ::strlen(text);
		
	  if (::fwrite(text, 1, len, f) != len)
	  {
		std::cerr << "Can't write data." << std::endl;
		return false;
	  }
		
	  ::fclose (f);
		
	  return true;
	}
private:
  std::string _name;
  bool _dir;
};

class autoproject
{
public:
  autoproject (std::string name, 
			   std::string version, 
			   std::string mail,
			   std::string author,
			   bool gnome = false)
	: _name (name),
	  _version (version),
	  _mail (mail),
	  _author (author)
	{
	  std::string srcdir (_name);
	  std::string conf (_name);
	  std::string makef (_name);
	  std::string srcmakef (_name);
	  std::string autorec (_name);
		
	  srcdir += "/src";
	  conf += "/configure.ac";
	  makef += "/Makefile.am";
	  srcmakef += "/src/Makefile.am";
	  autorec += "/autoreconf.sh";
		
	  file project (_name.c_str(), true);
	  file src (srcdir.c_str(), true);
	  file configure (conf.c_str());
	  file makefile (makef);
	  file srcmakefile (srcmakef);
	  file autoreconf (autorec);
		
	  // Create project dir
	  project.create ();
		
	  // Create "src" dir
	  src.create ();
		
	  // Create file configure.ac
	  configure.create ();
	  if (unlikely(gnome))
	  {
		ADD_CONFIGURE(CONFIGURE_GNOME_AC, configure);
	  }
	  else
	  {
		ADD_CONFIGURE(CONFIGURE_AC, configure);
	  }
		
	  // Create file Makefile.am
	  makefile.create ();
	  makefile.addText (MAKEFILE_AM);
		
	  // Create file Makefile.am in "src"
	  srcmakefile.create ();
	  ADD_PROYECT(SRC_MAKEFILE_AM, srcmakefile);
		
	  // Create config script
	  autoreconf.create ();
	  autoreconf.addText (AUTORECONF);
	  autoreconf.makeExecutable ();
		
	  //archivo(std::string(_nombre + "/INSTALL").c_str()).crear ();
	  file(std::string(_name + "/NEWS").c_str()).create ();
	  file(std::string(_name + "/README").c_str()).create ();
	  //archivo(std::string(_nombre + "/COPYING").c_str()).crear ();
	  file(std::string(_name + "/AUTHORS").c_str()).create ();
	  file(std::string(_name + "/ChangeLog").c_str()).create ();

#if 0
	  //
	  // We used to simlink ltmain.sh, but this is incorrect as ltmain.sh is
	  // needed, only, if libtool is in use.
	  //
 
	  struct stat st;
	  if (! ::stat ("/usr/share/libtool/config/ltmain.sh", &st)) {
	  } else if (! ::stat ("/usr/share/libtool/ltmain.sh", &st)) {
		  if (::symlink ("/usr/share/libtool/ltmain.sh", 
						 std::string(_name + "/ltmain.sh").c_str()))
		  {
			  std::cerr << "No se puede crear el enlace:" 
						<< ::strerror(errno)
						<< std::endl;
		  }
	  }
#endif
	}
private:
  std::string _name;
  std::string _version;
  std::string _mail;
  std::string _author;
  char _buf [4096];
};
