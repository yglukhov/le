//
// TestLuaValue.cpp
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

#include <sweet/unit/UnitTest.h>
#include <sweet/lua/Lua.hpp>
#include <sweet/lua/LuaValue.hpp>

using namespace sweet::lua;

SUITE( LuaValue )
{
    TEST( LuaValueLeavesValueOnStack )
    {
        Lua lua;
        lua_State* lua_state = lua.get_lua_state();
        lua_newtable( lua_state );
        LuaValue value( lua, -1 );
        CHECK( lua_istable(lua_state, -1) );
    }

    TEST( LuaValueReferencesString )
    {
        const char* STRING_VALUE = "string";
        Lua lua;
        lua_State* lua_state = lua.get_lua_state();
        lua_pushstring( lua_state, STRING_VALUE );
        LuaValue value( lua, -1 );
        lua_pop( lua_state, 1 );
        lua_gc( lua_state, LUA_GCCOLLECT, 0 );
        lua_push( lua_state, value );
        CHECK( lua_isstring(lua_state, -1) );
        CHECK_EQUAL( lua_tostring(lua_state, -1), STRING_VALUE );
    }

    TEST( LuaValueReferencesTable )
    {
        Lua lua;
        lua_State* lua_state = lua.get_lua_state();
        lua_newtable( lua_state );
        LuaValue value( lua, -1 );
        lua_pop( lua_state, 1 );
        lua_gc( lua_state, LUA_GCCOLLECT, 0 );
        lua_push( lua_state, value );
        CHECK( lua_istable(lua_state, -1) );
    }

    TEST( LuaValueCanBeCopied )
    {
        const char* STRING_VALUE = "string";
        Lua lua;
        lua_State* lua_state = lua.get_lua_state();
        lua_pushstring( lua_state, STRING_VALUE );
        LuaValue value( lua, -1 );
        lua_pop( lua_state, 1 );
        LuaValue other_value( value );
        lua_push( lua_state, value );
        lua_push( lua_state, other_value );
        CHECK( lua_equal(lua_state, -1, -2) );
    }
    
    TEST( DefaultConstructedLuaValueCanBeAssignedTo )
    {
        const char* STRING_VALUE = "string";
        Lua lua;
        lua_State* lua_state = lua.get_lua_state();
        lua_pushstring( lua_state, STRING_VALUE );
        LuaValue value( lua, -1 );
        lua_pop( lua_state, 1 );
        LuaValue other_value;
        other_value = value;
        lua_push( lua_state, value );
        lua_push( lua_state, other_value );
        CHECK( lua_equal(lua_state, -1, -2) );
    }
    
    TEST( LuaValueCanBeAssignedTo )
    {
        const char* STRING_VALUE = "string";
        Lua lua;
        lua_State* lua_state = lua.get_lua_state();
        lua_pushstring( lua_state, STRING_VALUE );
        LuaValue value( lua, -1 );
        lua_pop( lua_state, 1 );
        LuaValue other_value( value );
        other_value = value;
        lua_push( lua_state, value );
        lua_push( lua_state, other_value );
        CHECK( lua_equal(lua_state, -1, -2) );
    }
}
