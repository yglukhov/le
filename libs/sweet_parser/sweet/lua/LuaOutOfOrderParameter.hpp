//
// LuaOutOfOrderParameter.hpp
// Copyright (c) 2008 - 2012 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_LUAOUTOFORDERPARAMETER_HPP_INCLUDED
#define SWEET_LUA_LUAOUTOFORDERPARAMETER_HPP_INCLUDED

#include "declspec.hpp" 

namespace sweet
{

namespace lua
{

/**
// @internal
//
// A type to bind Lua parameters to C++ functions in a different order to
// what they appear in the function signature.
*/
template <int POSITION>
class LuaOutOfOrderParameter
{
public:
    LuaOutOfOrderParameter();
};

SWEET_LUA_DECLSPEC extern const LuaOutOfOrderParameter<1> _1;
SWEET_LUA_DECLSPEC extern const LuaOutOfOrderParameter<2> _2;
SWEET_LUA_DECLSPEC extern const LuaOutOfOrderParameter<3> _3;
SWEET_LUA_DECLSPEC extern const LuaOutOfOrderParameter<4> _4;
SWEET_LUA_DECLSPEC extern const LuaOutOfOrderParameter<5> _5;
SWEET_LUA_DECLSPEC extern const LuaOutOfOrderParameter<6> _6;
SWEET_LUA_DECLSPEC extern const LuaOutOfOrderParameter<7> _7;

}

}

#endif
