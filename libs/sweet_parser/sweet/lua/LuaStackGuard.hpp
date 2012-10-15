//
// LuaStackGuard.hpp
// Copyright (c) 2007 - 2010 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_LUASTACKGUARD_HPP_INCLUDED
#define SWEET_LUA_LUASTACKGUARD_HPP_INCLUDED

#include "declspec.hpp"
#include "lua_/lua.h"

namespace sweet
{

namespace lua
{

/**
// @internal
//
// A guard that ensures that the top level stack for a Lua state is restored
// when a scope is left even if an exception is thrown.
*/
class SWEET_LUA_DECLSPEC LuaStackGuard
{
    lua_State* lua_state_; ///< The Lua state to save and restore the top of the stack of.
    int restore_to_position_; ///< The position to restore the top of the stack to on destruction.

    public:
        LuaStackGuard( lua_State* lua_state, int restore_to_position_delta = 0 );
        ~LuaStackGuard();
        void reset_to_top_of_stack( int restore_to_position_delta = 0 );
};

}

}

#endif
