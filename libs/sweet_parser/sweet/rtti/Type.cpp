//
// Type.cpp
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

#include "Type.hpp"
#include <sweet/assert/assert.hpp>

using namespace sweet::rtti;

/**
// Constructor.
//
// @param TypeInfo
//  The type_info to wrap.
*/
Type::Type( const TypeInfo& type_info )
: type_info_( &type_info )
{
    SWEET_ASSERT( type_info_ );
}

/**
// Copy constructor.
//
// @param type
//  The Type to copy.
*/
Type::Type( const Type& type )
: type_info_( type.type_info_ )
{
    SWEET_ASSERT( type_info_ );
}

/**
// Assignment operator.
//
// @param type
//  The Type to assign from.
//
// @return
//  This Type.
*/
Type& Type::operator=( const Type& type )
{
    if ( this != &type )
    {
        type_info_ = type.type_info_;
        SWEET_ASSERT( type_info_ );
    }
    return *this;
}

/**
// Get the name of this Type.
//
// @return
//  The name.
*/
const char* Type::name() const
{
    return type_info_->name();
}

/**
// Equality operator.
//
// @param type
//  The Type to compare with.
//
// @return
//  True if this Type and \e type are equal otherwise false.
*/
bool Type::operator==( const Type& type ) const
{
    return *type_info_ == *type.type_info_;
}

/**
// Not equal operator.
//
// @param type
//  The Type to compare with.
//
// @return
//  True if this Type and \e type are not equal otherwise false.
*/
bool Type::operator!=( const Type& type ) const
{
    return *type_info_ != *type.type_info_;
}

/**
// Less than operator.
//
// @param type
//  The Type to compare with.
//
// @return
//  True if this Type is less than \e type otherwise false.
*/
bool Type::operator<( const Type& type ) const
{
    return type_info_->before( *type.type_info_ );
}
