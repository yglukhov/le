//
// LuaUserData.cpp
// Copyright (c) 2008  - 2010 Charles Baker.  All rights reserved.
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

#include "LuaUserData.hpp"

using namespace sweet;
using namespace sweet::lua;

/**
// Constructor.
//
// @param type
//  The rtti::Type of the user's data stored in this LuaUserData.
*/
LuaUserData::LuaUserData( const rtti::Type& type )
: type_( type )
{
}

/**
// Copy constructor.
//
// @param user_data
//  The LuaUserData to copy.
*/
LuaUserData::LuaUserData( const LuaUserData& user_data )
: type_( user_data.type_ )
{
}

/**
// Assignment operator.
//
// @param user_data
//  The LuaUserData to copy from.
//
// @return
//  This LuaUserData.
*/
LuaUserData& LuaUserData::operator=( const LuaUserData& user_data )
{
    if ( this != &user_data )
    {
        type_ = user_data.type_;
    }

    return *this;
}

/**
// Get the rtti::Type of this LuaUserData.
//
// @return
//  The rtti::Type.
*/
const rtti::Type& LuaUserData::type() const
{
    return type_;
}
