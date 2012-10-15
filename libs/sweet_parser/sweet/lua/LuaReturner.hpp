//
// LuaReturner.hpp
// Copyright (c) 2008 - 2010 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_LUARETURNER_INCLUDED
#define SWEET_LUA_LUARETURNER_INCLUDED

#include "LuaReturnerPolicy.hpp"
#include "lua_/lua.h"
#include <sweet/traits/traits.hpp>

namespace sweet
{

namespace lua
{

/**
// @internal
//
// A class template that with specializations provides the value 
// to return to Lua when a call from Lua into C++ returns and handles the
// different return value policies (see yield() and weaken()).
//
// The \e ReturnType parameter matches against the return type of functions so 
// that void functions return 0 and functions with other return types return 
// 1 to indicate that there is one value to be returned to Lua.
//
// The \e POLICY parameter matches a mask made up of LuaReturnerPolicy values.
*/
template <class ReturnType, int POLICY = LUA_POLICY_NULL>
struct LuaReturner
{
};

template <>
struct LuaReturner<void, LUA_POLICY_NULL>
{
    static int return_( lua_State* lua_state );
};

template <>
struct LuaReturner<void, LUA_POLICY_YIELD>
{
    static int return_( lua_State* lua_state );
};

template <>
struct LuaReturner<void, LUA_POLICY_WEAKEN>
{
    static int return_( lua_State* lua_state );
};

template <>
struct LuaReturner<void, LUA_POLICY_YIELD | LUA_POLICY_WEAKEN>
{
    static int return_( lua_State* lua_state );
};

template <class ReturnType>
struct LuaReturner<ReturnType, LUA_POLICY_NULL>
{
    static int return_( lua_State* lua_state, typename traits::traits<ReturnType>::parameter_type return_value );
};

template <class ReturnType>
struct LuaReturner<ReturnType, LUA_POLICY_YIELD>
{
    static int return_( lua_State* lua_state, typename traits::traits<ReturnType>::parameter_type return_value );
};

template <class ReturnType>
struct LuaReturner<ReturnType, LUA_POLICY_WEAKEN>
{
    static int return_( lua_State* lua_state, typename traits::traits<ReturnType>::parameter_type return_value );
};

template <class ReturnType>
struct LuaReturner<ReturnType, LUA_POLICY_YIELD | LUA_POLICY_WEAKEN>
{
    static int return_( lua_State* lua_state, typename traits::traits<ReturnType>::parameter_type return_value );
};

}

}

#endif
