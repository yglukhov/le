//
// LuaPosition.hpp
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

#ifndef SWEET_LUA_LUAPOSITION_HPP_INCLUDED
#define SWEET_LUA_LUAPOSITION_HPP_INCLUDED

#include "LuaOutOfOrderParameter.hpp"

namespace sweet
{

namespace lua
{

/**
// @internal
//
// A class template that (with specializations) provides the index that a 
// parameter value can be found at on the Lua stack.
*/
template <class Type, int POSITION>
struct LuaPosition
{
    enum { position = lua_upvalueindex(POSITION) };
};

/**
// @internal
//
// Provide the index for an out of order parameter.
*/
template <int POSITION, int IGNORED_POSITION>
struct LuaPosition<LuaOutOfOrderParameter<POSITION>, IGNORED_POSITION>
{
    enum { position = POSITION };
};

}

}

#endif
