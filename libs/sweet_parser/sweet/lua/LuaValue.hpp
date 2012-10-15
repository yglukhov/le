//
// LuaValue.hpp
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

#ifndef SWEET_LUA_LUAVALUE_HPP_INCLUDED
#define SWEET_LUA_LUAVALUE_HPP_INCLUDED

#include "declspec.hpp"

struct lua_State;

namespace sweet
{

namespace lua
{

class Lua;

/**
// Hold a reference to a value in Lua so that it doesn't get garbage 
// collected.
//
// Stores a reference to the Lua value in the Lua registry using the address
// of the LuaValue as a key so that Lua considers the value referenced and 
// available for garbage collection.
*/
class SWEET_LUA_DECLSPEC LuaValue
{
    Lua* lua_;
    
public:
    LuaValue();
    LuaValue( Lua& lua, int position );
    LuaValue( Lua& lua, lua_State* lua_state, int position );
    LuaValue( const LuaValue& value );
    LuaValue& operator=( const LuaValue& value );
    ~LuaValue();
};

}

}

#endif
