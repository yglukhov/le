//
// Option.hpp
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

#ifndef SWEET_CMDLINE_OPTION_HPP_INCLUDED
#define SWEET_CMDLINE_OPTION_HPP_INCLUDED

#include "declspec.hpp"
#include <string>

namespace sweet
{

namespace cmdline
{

/**
// @internal
//
// The type of data provided by a command line option.
*/
enum OptionType
{
    OPTION_BOOL,
    OPTION_INT,
    OPTION_FLOAT,
    OPTION_STRING
};

/**
// @internal
//
// An option that can be parsed from the command line.
*/
class SWEET_CMDLINE_DECLSPEC Option
{
    std::string name_; ///< The name of the option.
    std::string short_name_; ///< The short name of the option.
    std::string description_; ///< The description of the option.
    void* address_; ///< The address of the variable to receive the value of the option.
    OptionType type_; ///< The type of the option.

    public:
        Option( const std::string& name, const std::string& short_name, const std::string& description, void* address, OptionType type );
        const std::string& get_name() const;
        const std::string& get_short_name() const;
        const std::string& get_description() const;
        void* get_address() const;
        OptionType get_type() const;
};

}

}

#endif
