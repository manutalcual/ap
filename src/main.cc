//
// Programa: autoproyecto Copyright (c) 2006 Manuel Cano Muñoz
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
#include "main.hh"


#define equal(x,y) (::strcmp(x, y) == 0)

int main (int argc, char ** argv)
{

    if (argc < 2)
    {
		use ();
		std::cerr << "\n\tNot enough parameters.\n" << std::endl;
		exit (0);
    }
	
    int p = 1; // Initial position
    std::string project;
    std::string version ("0.1.0");
    std::string mail (USER);
    std::string author (FULL_NAME);
    bool gnome = false;
    bool help = false;
	
    for (; p < argc; ++p)
    {
		if (equal("-h", argv[p]) || equal("--help", argv[p]))
		{
			use ();
			exit (0);
		}
		else if (equal("-n", argv[p]))
		{
			project = argv[++p];
		}
		else if (equal("-v", argv[p]))
		{
			version = argv[++p];
		}
		else if (equal("-m", argv[p]))
		{
			mail = argv[++p];
		}
		else if (equal("--gnome", argv[p]))
		{
			gnome = true;
		}
		else if (equal("-h", argv[p]))
		{
			help = true;
		}
		else if (equal("--help", argv[p]))
		{
			help = true;
		}
		else if (equal("--author", argv[p]))
		{
			author = argv[++p];
		}
    }

    if (help)
    {
		use ();
		exit (0);
    }
	
    if (project == "")
    {
		std::cout << "There is no project name." << std::endl;
		use ();
		exit (0);
    }
	
    std::cout << "Creating project skeleton \"" 
			  << project << "\"" << std::endl;
	
    if (! gnome)
    {
		std::cout << "\tProject without GNOME." << std::endl;
    }
    autoproject ap (project, version, mail, author, gnome);
    makeBody (project, author);
	
    return 0;
}


void use ()
{
    std::cerr << "autoproject (c) 2006 " << FULL_NAME << std::endl;
    std::cerr << "Parameters:" << std::endl;
    std::cerr << "-h \tThis help text." << std::endl;
    std::cerr << "-n \tProject name." << std::endl;
    std::cerr << "-v \tProject version. (Default 0.1.0)" << std::endl;
    std::cerr << "-m \tEmail. (Default " << USER << ")" << std::endl;
}

//
// Makes program body
// Parameters:
// name		- Program name
// author	- Program author
//
void makeBody (std::string name, std::string author)
{
    //
    // Main file always "main"
    //
    std::string he (name); // Header
    std::string bo (name); // Body
	
    he += "/src/main.hh";
    bo += "/src/main.cc";
	
    std::ofstream header (he.c_str());
    std::ofstream body (bo.c_str());

    time_t t = ::time(0);
    struct tm * mytime = ::localtime(&t);

    header << "//-*- mode: c++; indent-tabs-mode: t; -*-\n//\n";
    header << "// Program: " << name << " Copyright (c) " 
		   << (mytime->tm_year + 1900) << " " << FULL_NAME << "\n";
    header << "// Author: " << USER << "\n";
    header << "// Date: " << ::ctime(&t) << "\n";
	header << "//";
	header << "//   This program is free software; you can redistribute it and/or modify";
	header << "//   it under the terms of the GNU General Public License as published by";
	header << "//   the Free Software Foundation; either version 2 of the License, or";
	header << "//   (at your option) any later version.";
	header << "//";
	header << "//   This program is distributed in the hope that it will be useful,";
	header << "//   but WITHOUT ANY WARRANTY; without even the implied warranty of";
	header << "//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the";
	header << "//   GNU General Public License for more details.";
	header << "//";
	header << "//   You should have received a copy of the GNU General Public License";
	header << "//   along with this program; if not, write to the Free Software";
	header << "//   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA";
	header << "//   02110-1301	USA";
	header << "//";
    header << "//\n";
    header << "// Includes\n";
    header << "//\n";
    header << "\n";
    header << "\n";

    body << "//-*- mode: c++; indent-tabs-mode: t; -*-\n//\n";
    body << "// Program: " << name << " Copyright (c) " 
		 << (mytime->tm_year + 1900) << " " << FULL_NAME << "\n";
    body << "// Author: " << USER << "\n";
    body << "// Date: " << ::ctime(&t);

	body << "//";
	body << "//   This program is free software; you can redistribute it and/or modify";
	body << "//   it under the terms of the GNU General Public License as published by";
	body << "//   the Free Software Foundation; either version 2 of the License, or";
	body << "//   (at your option) any later version.";
	body << "//";
	body << "//   This program is distributed in the hope that it will be useful,";
	body << "//   but WITHOUT ANY WARRANTY; without even the implied warranty of";
	body << "//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the";
	body << "//   GNU General Public License for more details.";
	body << "//";
	body << "//   You should have received a copy of the GNU General Public License";
	body << "//   along with this program; if not, write to the Free Software";
	body << "//   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA";
	body << "//   02110-1301	USA";
	body << "//";

    body << "//\n";
    body << "// Includes\n";
    body << "//\n";
    body << "#include \"main.hh\"\n";
    body << "\n";
    body << "\n";
    body << "int main (int argc, char ** argv)\n";
    body << "{\n";
    body << "\n";
    body << "\treturn 0;\n";
    body << "}\n";
    body << "\n";
    body << "\n";
    body << "\n";
}
