//
// cmdline.hpp
// Copyright (c) 2008 - 2012 Charles Baker.  All rights reserved.
//    
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//

#ifndef SWEET_CMDLINE_HPP_INCLUDED
#define SWEET_CMDLINE_HPP_INCLUDED

#ifndef BUILD_MODULE_CMDLINE
#pragma comment( lib, "cmdline" BUILD_LIBRARY_SUFFIX )
#endif

namespace sweet
{

/**
 Command line parsing library.
 
 Parses arguments from the command line as specified by the POSIX and GNU
 standards.  See http://www.informit.com/articles/article.aspx?p=175771.

 Usage is to construct a Parser object on the stack, add command line options
 to it, and then parse command lines (as argc/argv pairs). 

@code
bool        help    = false;
bool        version = false;
bool        quiet   = false;
int         integer = 0;
float       real    = 0.0f;
std::string string  = "";
std::vector<std::string> input_files;

cmdline::Parser command_line_parser;
command_line_parser.add_options()
    ( "help",    "h", "Print this message and exit",           &help    )
    ( "version", "v", "Print the version and exit",            &version )
    ( "quiet",   "q", "Prevent the output of status messages", &quiet   )
    ( "integer", "i", "An integer argument",                   &integer )
    ( "real",    "r", "A real argument",                       &real    )
    ( "string",  "s", "A string argument",                     &string  )
    ( &input_files )
;

command_line_parser.parse( argc, argv );
@endcode

 The Parser is also able to generate a help message that displays all of the
 options that have been added to it along with their descriptions.

@code
if ( help )
{
    std::cout << " \n";
    std::cout << "Usage: example [options] [files] \n";
    std::cout << "Options: \n";
    command_line_parser.print( stdout );
}
@endcode
*/
namespace cmdline
{
}

}

#include "Error.hpp"
#include "Option.hpp"
#include "AddOption.hpp"
#include "Parser.hpp"

#endif
