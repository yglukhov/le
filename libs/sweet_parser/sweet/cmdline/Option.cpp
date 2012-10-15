//
// Option.cpp
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

#include "Option.hpp"
#include <sweet/assert/assert.hpp>

using namespace sweet::cmdline;

/**
// Constructor.
//
// @param name
//  The name (or an empty string if this Option doesn't have a name).
//
// @param short_name
//  The short version of the name (or an empty string if this Option doesn't 
//  have a short name).
//
// @param description
//  The description displayed when this Option is printed.
//
// @param address
//  The address of the variable that this Option sets.
//
// @param type
//  The OptionType that specifies the type of variable pointed to by 
//  \e address.
*/
Option::Option( const std::string& name, const std::string& short_name, const std::string& description, void* address, OptionType type )
: name_( name ),
  short_name_( short_name ),
  description_( description ),
  address_( address ),
  type_( type )
{
    SWEET_ASSERT( !name.empty() || !short_name.empty() );
    SWEET_ASSERT( address_ );
}

/**
// Get the name of this Option.
//
// @return
//  The name.
*/
const std::string& Option::get_name() const
{
    return name_;
}

/**
// Get the short name of this Option.
//
// @return
//  The short name.
*/
const std::string& Option::get_short_name() const
{
    return short_name_;
}

/**
// Get the description of this Option.
//
// @return
//  The description.
*/
const std::string& Option::get_description() const
{
    return description_;
}

/**
// Get the address of the variable that this Option sets.
//
// @return
//  The address of the variable that this Option sets.
*/ 
void* Option::get_address() const
{
    return address_;
}

/**
// Get the OptionType of this Option.
//
// @return
//  The OptionType.
*/
OptionType Option::get_type() const
{
    return type_;
}
