//
// AddOption.cpp
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

#include "AddOption.hpp"
#include <sweet/assert/assert.hpp>

using std::vector;
using namespace sweet::cmdline;

/**
// Constructor.
//
// @param options
//  The vector of Options to add Options to (assumed to be not null).
//
// @param operands
//  The variable to set to point to the vector of strings to store operands 
//  in (assumed to be not null).
*/
AddOption::AddOption( std::vector<Option>* options, std::vector<std::string>** operands )
: options_( options ),
  operands_( operands )
{
    SWEET_ASSERT( options_ );
    SWEET_ASSERT( operands_ );
}

/**
// Add a boolean Option.
//
// @param name
//  The name of the Option to add (or an empty string if the Option
//  doesn't have a name).
//
// @param short_name
//  The short name of the Option to add (or an empty string if the Option
//  doesn't have a short name).
//
// @param description
//  The description of the Option to be displayed when it is printed.
//
// @param address
//  The address of the boolean that the Option sets the value of.
//
// @return
//  This AddOption.
*/
AddOption& AddOption::operator()( const std::string& name, const std::string& short_name, const std::string& description, bool* address )
{
    options_->push_back( Option(name, short_name, description, address, OPTION_BOOL) );
    return *this;
}

/**
// Add an integer Option.
//
// @param name
//  The name of the Option to add (or an empty string if the Option
//  doesn't have a name).
//
// @param short_name
//  The short name of the Option to add (or an empty string if the Option
//  doesn't have a short name).
//
// @param description
//  The description of the Option to be displayed when it is printed.
//
// @param address
//  The address of the int that the Option sets the value of.
//
// @return
//  This AddOption.
*/
AddOption& AddOption::operator()( const std::string& name, const std::string& short_name, const std::string& description, int* address )
{
    options_->push_back( Option(name, short_name, description, address, OPTION_INT) );
    return *this;
}

/**
// Add a float Option.
//
// @param name
//  The name of the Option to add (or an empty string if the Option
//  doesn't have a name).
//
// @param short_name
//  The short name of the Option to add (or an empty string if the Option
//  doesn't have a short name).
//
// @param description
//  The description of the Option to be displayed when it is printed.
//
// @param address
//  The address of the float that the Option sets the value of.
//
// @return
//  This AddOption.
*/
AddOption& AddOption::operator()( const std::string& name, const std::string& short_name, const std::string& description, float* address )
{
    options_->push_back( Option(name, short_name, description, address, OPTION_FLOAT) );
    return *this;
}

/**
// Add a string Option.
//
// @param name
//  The name of the Option to add (or an empty string if the Option
//  doesn't have a name).
//
// @param short_name
//  The short name of the Option to add (or an empty string if the Option
//  doesn't have a short name).
//
// @param description
//  The description of the Option to be displayed when it is printed.
//
// @param address
//  The address of the std::string that the Option sets the value of.
//
// @return
//  This AddOption.
*/
AddOption& AddOption::operator()( const std::string& name, const std::string& short_name, const std::string& description, std::string* address )
{
    options_->push_back( Option(name, short_name, description, address, OPTION_STRING) );
    return *this;
}

/**
// Set the vector of strings to store operands from the command line in.
//
// @param operands
//  The variable to set to point to the vector of strings to store operands
//  in.
//
// @return
//  This AddOption.
*/
AddOption& AddOption::operator()( std::vector<std::string>* operands )
{
    SWEET_ASSERT( operands_ );
    *operands_ = operands;
    return *this;
}

