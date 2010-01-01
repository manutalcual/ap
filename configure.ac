AC_INIT([ap], [0.1.0], [manuel])
AC_CONFIG_SRCDIR([src/main.cc])
AM_INIT_AUTOMAKE()
AM_CONFIG_HEADER(config.h)

# Checks for programs.
AC_PROG_CXX
#AC_PROG_CC
#AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
#AC_CHECK_HEADERS([sys/types.h sys/socket.h stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
#AC_ARG_WITH([categoria],
#	AC_HELP_STRING([--with-categoria=CAT],
#	[Definir categoria de log]),
#	[categoria=$withval], [LOG_CATEGORIA=DEBUG])

#if test "$categoria" != ""; then
#	CXXFLAGS="$CXXFLAGS -DLOG_CATEGORIA=\\"$categoria\\""
#fi

# Checks for library functions.

#AC_SUBST(CFLAGS)
#AC_SUBST(CPPFLAGS)
#AC_SUBST(LDFLAGS)

AC_ARG_WITH([user], 
            AC_HELP_STRING([--with-user=USER],
            [Defines user's name]),
            [user=$withval], [user="`whoami`@`hostname`"])

#AC_CACHE_CHECK([wether to use a custom user email.],
#               [user], [echo -n no])

if test "$user" != ""; then
   CXXFLAGS="$CXXFLAGS -DUSER=\\\"$user\\\""
fi

AC_ARG_WITH([full-name], 
            AC_HELP_STRING([--with-full-name=FULL_NAME],
            [Defines user's name for copyright notice]),
            [full_name=$withval], [full_name=`whoami`])

#AC_CACHE_CHECK([wether to use a custom full name for copyright],
#               [full_name], [echo -n no])

if test "$full_name" != ""; then
   CXXFLAGS="$CXXFLAGS -DFULL_NAME=\"\\\"$full_name\\\"\""
fi


AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
