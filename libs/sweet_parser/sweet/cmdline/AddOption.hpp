//
// AddOption.hpp
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

#ifndef SWEET_CMDLINE_ADDOPTION_HPP_INCLUDED
#define SWEET_CMDLINE_ADDOPTION_HPP_INCLUDED

#include "declspec.hpp"
#include "Option.hpp"
#include <string>
#include <vector>

namespace sweet
{

namespace cmdline
{

/**
// @internal
//
// A helper class that provides a convenient syntax for adding Options to a
// Parser.
*/
class SWEET_CMDLINE_DECLSPEC AddOption
{
    std::vector<Option>* options_; ///< The vector to add Options to.
    std::vector<std::string>** operands_; ///< The pointer to set to point to the vector of strings to store operands to.

    public:
        AddOption( std::vector<Option>* options, std::vector<std::string>** operands );
        AddOption& operator()( const std::string& name, const std::string& short_name, const std::string& description, bool* address );
        AddOption& operator()( const std::string& name, const std::string& short_name, const std::string& description, int* address );
        AddOption& operator()( const std::string& name, const std::string& short_name, const std::string& description, float* address );
        AddOption& operator()( const std::string& name, const std::string& short_name, const std::string& description, std::string* address );
        AddOption& operator()( std::vector<std::string>* operands );
};

}

}

#endif
