//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 2 of the License, or
//  (at your option) version 3.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.

//  You should have received a copy of the GNU Lesser General Public License
//  along with this program; if not, write to the
//  Free Software Foundation, Inc.,
//  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "Terminal.hpp"
#include "Configuration.hpp"

extern char *program_invocation_name;
extern char *program_invocation_short_name;

void Terminal::Message(std::string text)
{
    std::cout << text << std::endl;
}

void Terminal::Error(std::string text)
{
    std::cerr << program_invocation_short_name << ": error: " << text << std::endl;
}

Terminal::Terminal()
{
    //ctor
}

Terminal::~Terminal()
{
    //dtor
}

bool Terminal::Parse(int argc, char * argv[])
{
    if (argc == 0)
    {
        // something went horribly wrong here
        Terminal::Error("Invalid number of arguments: 0");
        return false;
    }

    // we use GNU getopt here, feel free to replace with whatever that is effective
    int c;
    while (true)
    {
        static struct option long_options[] =
        {
            // These options set a flag.
            {"verbose", no_argument,          NULL, 'v'},
            {"help",    no_argument,          NULL, 'h'},
            {"version", no_argument,          NULL, 'V'},
            {"debug",   no_argument,          NULL, 'd'},
            {"output",  required_argument,    NULL, 'o'},
            {0, 0, 0, 0}
        };
        // getopt_long stores the option index here.
        int option_index = 0;
        c = getopt_long (argc, argv, "hVv", long_options, &option_index);
        // Detect the end of the options.
        if (c == -1)
            break;
        switch (c)
        {
            case 'V':
                DisplayVersion();
                return false;
            case 'h':
                DisplayHelp();
                return false;
            case 'd':
                break;
            case 'v':
                Configuration::Verbosity++;
                break;
            case 'o':
                Configuration::Target = std::string(optarg);
                break;
            case '?':
                return false;
                break;
        }
    }
    if (optind < argc)
    {
        // we don't support more than one input file so far
        Configuration::Configure_Ac = argv[optind];
    }
    return true;
}

void Terminal::DisplayHelp()
{
    Terminal::Message("Usage: autoconf2 [OPTION]... [TEMPLATE-FILE]...\n\n"\
                      "Generate a configuration script from a TEMPLATE-FILE if given, or\n"\
                      "`configure.ac' if present, or else `configure.in'.  Output is sent\n"\
                      "to the standard output if TEMPLATE-FILE is given, else into\n"\
                      "`configure'.\n\n"\
                      "Operation modes:\n"\
                      "  -h, --help                print this help, then exit\n"\
                      "  -V, --version             print version number, then exit\n"\
                      "  -v, --verbose             verbosely report processing\n"\
                      "  -d, --debug               don't remove temporary files\n"\
                      "  -f, --force               consider all files obsolete\n"\
                      "  -o, --output=FILE         save output in FILE (stdout is the default)\n"\
                      "  -W, --warnings=CATEGORY   report the warnings falling in CATEGORY [syntax]\n"\
                      "Warning categories include:\n"\
                      "  `cross'         cross compilation issues\n"\
                      "  `obsolete'      obsolete constructs\n"\
                      "  `syntax'        dubious syntactic constructs\n"\
                      "  `all'           all the warnings\n"\
                      "  `no-CATEGORY'   turn off the warnings on CATEGORY\n"\
                      "  `none'          turn off all the warnings\n"\
                      "  `error'         warnings are error\n\n"\
                      "The environment variables `M4' and `WARNINGS' are honored.\n\n"\
                      "Library directories:\n"\
                      "  -B, --prepend-include=DIR  prepend directory DIR to search path\n"\
                      "  -I, --include=DIR          append directory DIR to search path\n\n"\
                      "Tracing:\n"\
                      "  -t, --trace=MACRO[:FORMAT]  report the list of calls to MACRO\n"\
                      "  -i, --initialization        also trace Autoconf's initialization process\n\n"\
                      "In tracing mode, no configuration script is created.  FORMAT defaults\n"\
                      "to `$f:$l:$n:$%'; see `autom4te --help' for information about FORMAT.\n\n"\
                      "Report bugs to <benapetr@gmail.com>.\n\n"
                      "Autoconf2 home page: <https://github.com/benapetr/autotools2>.");
}

void Terminal::DisplayVersion()
{
    Terminal::Message("autoconf2 "\
                        PROGRAM_VERSION\
                        "\nCopyright (C) 2014 Petr Bena (benapetr@gmail.com)\n"\
                        "License LGPL: GNU Lesser GPL version 3 or later\n"\
                        "<http://gnu.org/licenses/lgpl.html>, <http://gnu.org/licenses/exceptions.html>\n\n"\
                        "This is free software: you are free to change and redistribute it.\n"\
                        "There is NO WARRANTY, to the extent permitted by law.\n\n"\
                        "Written by "\
                        PROGRAM_AUTHORS);
}
