//
// LuaValue.cpp
// Copyright (c) 2011 Charles Baker.  All rights reserved.
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

#include "stdafx.hpp"
#include "LuaValue.hpp"
#include "LuaConverter.hpp"
#include "Lua.hpp"

using namespace sweet::lua;

LuaValue::LuaValue()
: lua_( NULL )
{
}

LuaValue::LuaValue( Lua& lua, int position )
: lua_( &lua )
{
    SWEET_ASSERT( lua_ );
    lua_State* lua_state = lua_->get_lua_state();
    SWEET_ASSERT( lua_state );    
    lua_pushvalue( lua_state, position );
    lua_pushlightuserdata( lua_state, this );
    lua_insert( lua_state, -2 );
    lua_rawset( lua_state, LUA_REGISTRYINDEX );    
}

LuaValue::LuaValue( Lua& lua, lua_State* lua_state, int position )
: lua_( &lua )
{
    SWEET_ASSERT( lua_ );
    SWEET_ASSERT( lua_state );
    lua_pushvalue( lua_state, position );
    lua_pushlightuserdata( lua_state, this );
    lua_insert( lua_state, -2 );
    lua_rawset( lua_state, LUA_REGISTRYINDEX );    
}

LuaValue::LuaValue( const LuaValue& value )
: lua_( value.lua_ )
{
    if ( lua_ )
    {        
        lua_State* lua_state = lua_->get_lua_state();
        SWEET_ASSERT( lua_state );
        lua_pushlightuserdata( lua_state, this );
        lua_push( lua_state, value );
        lua_rawset( lua_state, LUA_REGISTRYINDEX );        
    }
}

LuaValue& LuaValue::operator=( const LuaValue& value )
{
    if ( this != &value )
    {
        if ( lua_ && lua_ != value.lua_ )
        {
            lua_State* lua_state = lua_->get_lua_state();
            SWEET_ASSERT( lua_state );
            lua_pushlightuserdata( lua_state, this );
            lua_pushnil( lua_state );
            lua_rawset( lua_state, LUA_REGISTRYINDEX );
        }
        
        lua_ = value.lua_;
        
        if ( lua_ )
        {
            lua_State* lua_state = lua_->get_lua_state();
            SWEET_ASSERT( lua_state );
            lua_pushlightuserdata( lua_state, this );
            lua_push( lua_state, value );
            lua_rawset( lua_state, LUA_REGISTRYINDEX );        
        }
    }
    return *this;
}

LuaValue::~LuaValue()
{
    if ( lua_ )
    {
        lua_State* lua_state = lua_->get_lua_state();
        SWEET_ASSERT( lua_state );
        lua_pushlightuserdata( lua_state, this );
        lua_pushnil( lua_state );
        lua_rawset( lua_state, LUA_REGISTRYINDEX );
        lua_ = NULL;
    }
}
