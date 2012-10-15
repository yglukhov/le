//
// LuaReturner.ipp
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

#ifndef SWEET_LUA_LUA_LUARETURNER_IPP_INCLUDED
#define SWEET_LUA_LUA_LUARETURNER_IPP_INCLUDED

#include "LuaReturner.hpp"
#include "LuaReturnerPolicy.hpp"
#include "lua_/lua.h"

namespace sweet
{

namespace lua
{

inline int LuaReturner<void, LUA_POLICY_NULL>::return_( lua_State* lua_state )
{
    return 0;
}

inline int LuaReturner<void, LUA_POLICY_YIELD>::return_( lua_State* lua_state )
{
    SWEET_ASSERT( lua_state );
    return lua_yield( lua_state, 0 );
}

inline int LuaReturner<void, LUA_POLICY_YIELD | LUA_POLICY_WEAKEN>::return_( lua_State* lua_state )
{
    SWEET_ASSERT( lua_state );
    return lua_yield( lua_state, 0 );
}

template <class ReturnType>
int LuaReturner<ReturnType, LUA_POLICY_NULL>::return_( lua_State* lua_state, typename traits::traits<ReturnType>::parameter_type value )
{
    SWEET_ASSERT( lua_state );
    LuaConverter<ReturnType>::push( lua_state, value );
    return 1;
}

template <class ReturnType>
int LuaReturner<ReturnType, LUA_POLICY_YIELD>::return_( lua_State* lua_state, typename traits::traits<ReturnType>::parameter_type value )
{
    SWEET_ASSERT( lua_state );
    LuaConverter<ReturnType>::push( lua_state, value );
    return lua_yield( lua_state, 1 );
}

template <class ReturnType>
int LuaReturner<ReturnType, LUA_POLICY_WEAKEN>::return_( lua_State* lua_state, typename traits::traits<ReturnType>::parameter_type value )
{
    SWEET_ASSERT( lua_state );
    typedef typename traits::traits<ReturnType>::base_type base_type;
    LuaObjectConverter<ReturnType, typename LuaTraits<base_type>::storage_type>::weaken( lua_state, value );
    LuaObjectConverter<ReturnType, typename LuaTraits<base_type>::storage_type>::push( lua_state, value );
    return 1;
}

template <class ReturnType>
int LuaReturner<ReturnType, LUA_POLICY_YIELD | LUA_POLICY_WEAKEN>::return_( lua_State* lua_state, typename traits::traits<ReturnType>::parameter_type value )
{
    SWEET_ASSERT( lua_state );
    typedef typename traits::traits<ReturnType>::base_type base_type;
    LuaObjectConverter<ReturnType, typename LuaTraits<base_type>::storage_type>::weaken( lua_state, value );
    LuaObjectConverter<ReturnType, typename LuaTraits<base_type>::storage_type>::push( lua_state, value );
    return lua_yield( lua_state, 1 );
}

}

}

#endif
