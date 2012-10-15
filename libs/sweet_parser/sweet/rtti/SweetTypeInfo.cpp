//
// SweetTypeInfo.cpp
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

#include "SweetTypeInfo.hpp"
#include <sweet/assert/assert.hpp>
#include <sweet/build.hpp>

using namespace sweet::rtti;

#ifdef SWEET_RTTI_SWEET_RTTI_ENABLED

/**
// Constructor.
//
// @param name
//  The name of the type.
*/
SweetTypeInfo::SweetTypeInfo( const char* name )
: name_( name )
{
    SWEET_ASSERT( name_ );
}

/**
// Get the name of this SweetTypeInfo.
//
// @return
//  The name.
*/
const char* SweetTypeInfo::name() const
{
    return name_;
}

/**
// Get the raw name of this SweetTypeInfo.
//
// @return
//  The raw name.
*/
const char* SweetTypeInfo::raw_name() const
{
    return name_;
}

/**
// Does this SweetTypeInfo order before \e user_type_info?
//
// @param user_type_info
//  The SweetTypeInfo to compare with.
//
// @return
//  True if this SweetTypeInfo orders before \e user_type_info otherwise 
//  false.
*/
bool SweetTypeInfo::before( const SweetTypeInfo& user_type_info ) const
{
    return name_ < user_type_info.name_;
}

/**
// Equal operator.
//
// @param type_info
//  The SweetTypeInfo to compare with.
//
// @return
//  True if this SweetTypeInfo and \e type_info are for the same type 
//  otherwise false.
*/
bool SweetTypeInfo::operator==( const SweetTypeInfo& type_info ) const
{
    return name_ == type_info.name_;
}

/**
// Not equal operator.
//
// @param type_info
//  The SweetTypeInfo to compare with.
//
// @return
//  True if this SweetTypeInfo and \e type_info are not for the same type 
//  otherwise false.
*/
bool SweetTypeInfo::operator!=( const SweetTypeInfo& type_info ) const
{
    return name_ != type_info.name_;
}

#endif
