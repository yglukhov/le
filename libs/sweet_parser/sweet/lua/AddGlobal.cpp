//
// AddGlobal.cpp
// Copyright (c) 2007 - 2011 Charles Baker.  All rights reserved.
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

#include "AddGlobal.hpp"
#include "LuaStackGuard.hpp"
#include "LuaRawWrapper.hpp"
#include <sweet/assert/assert.hpp>

using namespace sweet::lua;

/**
// Constructor.
// 
// @param lua_state
//  The lua_State to set values in.
*/
AddGlobal::AddGlobal( lua_State* lua )
: lua_state_( lua )
{
    SWEET_ASSERT( lua_state_ );
}

/**
// Set a global variable to nil.
//
// @param name
//  The name of the variable to set to nil.
//
// @param nil
//  The LuaNil used to overload this function (ignored).
//
// @return
//  This AddGlobal.
*/
AddGlobal& AddGlobal::operator()( const char* name, const LuaNil& nil )
{
    SWEET_ASSERT( lua_state_ );
    SWEET_ASSERT( name );

    LuaStackGuard guard( lua_state_ );
    lua_pushnil( lua_state_ );
    lua_setglobal( lua_state_, name );
    return *this;
}

/**
// Set a global variable to the global environment.
//
// @param name
//  The name of the variable to set to the global environment.
//
// @param global_environment
//  The LuaGlobalEnvironment used to overload this function (ignored).
//
// @return
//  This AddGlobal.
*/
AddGlobal& AddGlobal::operator()( const char* name, const LuaGlobalEnvironment& global_environment )
{
    SWEET_ASSERT( lua_state_ );
    SWEET_ASSERT( name );

    LuaStackGuard guard( lua_state_ );
    lua_pushvalue( lua_state_, LUA_GLOBALSINDEX );
    lua_setglobal( lua_state_, name );
    return *this;
}

/**
// Set a global variable to a boolean value.
//
// @param name
//  The name of the variable to put the boolean value in.
//
// @param value
//  The value of the variable to add.
//
// @return
//  This AddGlobal object.
*/
AddGlobal& AddGlobal::operator()( const char* name, bool value )
{
    SWEET_ASSERT( lua_state_ );
    SWEET_ASSERT( name );

    LuaStackGuard guard( lua_state_ );
    lua_pushboolean( lua_state_, value ? 1 : 0 );
    lua_setglobal( lua_state_, name );
    return *this;
}

/**
// Set a global variable to an integer value.
//
// @param name
//  The name of the variable to put the integer value in.
//
// @param value
//  The value of the variable to add.
//
// @return
//  This AddGlobal object.
*/
AddGlobal& AddGlobal::operator()( const char* name, int value )
{
    SWEET_ASSERT( lua_state_ );
    SWEET_ASSERT( name );

    LuaStackGuard guard( lua_state_ );
    lua_pushnumber( lua_state_, static_cast<lua_Number>(value) );
    lua_setglobal( lua_state_, name );
    return *this;
}

/**
// Set a global variable to a floating point value.
//
// @param name
//  The name of the variable to put the float value in.
//
// @param value
//  The value of the variable to add.
//
// @return
//  This AddGlobal object.
*/
AddGlobal& AddGlobal::operator()( const char* name, float value )
{
    SWEET_ASSERT( lua_state_ );
    SWEET_ASSERT( name );

    LuaStackGuard guard( lua_state_ );
    lua_pushnumber( lua_state_, static_cast<lua_Number>(value) );
    lua_setglobal( lua_state_, name );
    return *this;
}

/**
// Set a global variable to a string value.
//
// @param name
//  The name of the variable to put the string value in.
//
// @param value
//  The value of the variable to add.
//
// @return
//  This AddGlobal object.
*/
AddGlobal& AddGlobal::operator()( const char* name, const char* value )
{
    SWEET_ASSERT( lua_state_ );
    SWEET_ASSERT( name );
    SWEET_ASSERT( value );

    LuaStackGuard guard( lua_state_ );
    lua_pushstring( lua_state_, value );
    lua_setglobal( lua_state_, name );
    return *this;
}

/**
// Set a global variable to a string value.
//
// @param name
//  The name of the variable to put the string value in.
//
// @param value
//  The value of the variable to add.
//
// @return
//  This AddGlobal object.
*/
AddGlobal& AddGlobal::operator()( const char* name, const std::string& value )
{
    SWEET_ASSERT( lua_state_ );
    SWEET_ASSERT( name );

    LuaStackGuard guard( lua_state_ );
    lua_pushlstring( lua_state_, value.c_str(), value.length() );
    lua_setglobal( lua_state_, name );
    return *this;
}

/**
// Set a global variable to refer to a raw function with no up values.
//
// @param name
//  The name of the variable to put the object in.
//
// @param raw_wrapper
//  The LuaRawWrapper that wraps the raw function.
//
// @return
//  This AddGlobal object.
*/
AddGlobal& AddGlobal::operator()( const char* name, const LuaRawWrapper& raw_wrapper )
{
    SWEET_ASSERT( lua_state_ );
    SWEET_ASSERT( name );

    LuaStackGuard guard( lua_state_ );
    lua_pushcclosure( lua_state_, raw_wrapper.get_function(), 0 );
    lua_setglobal( lua_state_, name );
    return *this;
}
