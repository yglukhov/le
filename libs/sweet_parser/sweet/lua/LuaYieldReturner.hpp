//
// LuaYieldReturner.hpp
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

#ifndef SWEET_LUA_LUAYIELDRETURNER_HPP_INCLUDED
#define SWEET_LUA_LUAYIELDRETURNER_HPP_INCLUDED

#include "declspec.hpp"

namespace sweet
{

namespace lua
{

/**
// @internal
//
// A class template that (with a single specialization) provides the value 
// to return to Lua when a call from Lua into C++ yields and determines 
// whether or not to weaken the returned value (assuming that there is a 
// returned value and that value is an object).
//
// The single specialization matches void functions and calls lua_yield() with
// \e nresults equal to 0 because void functions yield without providing 
// results.  The default implementation matches all other cases and calls 
// lua_yield() with \e nresults equal to 1 to indicate that a single result
// has been provided.
//
// The value returned by the call to lua_yield() is returned as the result of
// calling LuaYieldReturner::return_value().
*/
template <class ReturnType>
class LuaYieldReturner
{
    public:
        static int return_value( lua_State* lua_state );
};

/**
// @internal
//
// Call lua_yield() with \e nresults equal to 0 for functions that don't yield
// without providing results.
*/
template <>
class SWEET_LUA_DECLSPEC LuaYieldReturner<void>
{
    public:
        static int return_value( lua_State* lua_state );
};

}

}

#endif
