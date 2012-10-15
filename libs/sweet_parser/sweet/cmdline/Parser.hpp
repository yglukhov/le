//
// Parser.hpp
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

#ifndef SWEET_CMDLINE_PARSER_HPP_INCLUDED
#define SWEET_CMDLINE_PARSER_HPP_INCLUDED

#include "declspec.hpp"
#include "Option.hpp"
#include "AddOption.hpp"
#include <string>
#include <vector>
#include <stdio.h>

namespace sweet
{

namespace cmdline
{

/**
// A command line options parser.
*/
class SWEET_CMDLINE_DECLSPEC Parser
{
    std::vector<Option> options_; ///< The Options that this Parser will parse from the command line.
    std::vector<std::string>* operands_; ///< The vector of strings that this Parser will parse operands from the command line into.

    public:
        Parser();
        AddOption add_options();
        void parse( int argc, char** argv ) const;
        void parse( int argc, const char** argv ) const;
        void print( FILE* stream, int width = 12 ) const;

    private:
        bool is_short_option( const char* argument ) const;
        bool is_long_option( const char* argument ) const;
        const Option* find_option_by_name( const std::string& name ) const;
        const Option* find_option_by_short_name( const std::string& short_name ) const;
        const char* find_end_of_name( const char* name ) const;
        const char* find_argument( const char* name_end ) const;
        int parse_option( const Option* option, const char* argument, const char* next_argument ) const;
};

}

}

#endif
