//
// LuaOutOfOrderParameter.cpp
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

#include "LuaOutOfOrderParameter.hpp"

using namespace sweet::lua;

/** 
// Represents the first %Lua parameter when adding global or member functions.
*/
const sweet::lua::LuaOutOfOrderParameter<1> sweet::lua::_1;

/** 
// Represents the second %Lua parameter when adding global or member 
// functions.
*/
const sweet::lua::LuaOutOfOrderParameter<2> sweet::lua::_2;

/** 
// Represents the third %Lua parameter when adding global or member functions.
*/
const sweet::lua::LuaOutOfOrderParameter<3> sweet::lua::_3;

/** 
// Represents the fourth %Lua parameter when adding global or member 
// functions.
*/
const sweet::lua::LuaOutOfOrderParameter<4> sweet::lua::_4;

/** 
// Represents the fifth %Lua parameter when adding global or member functions.
*/
const sweet::lua::LuaOutOfOrderParameter<5> sweet::lua::_5;

/** 
// Represents the sixth %Lua parameter when adding global or member functions.
*/
const sweet::lua::LuaOutOfOrderParameter<6> sweet::lua::_6;

/** 
// Represents the seventh %Lua parameter when adding global or member 
// functions.
*/
const sweet::lua::LuaOutOfOrderParameter<7> sweet::lua::_7;

template <int POSITION> LuaOutOfOrderParameter<POSITION>::LuaOutOfOrderParameter()
{
}
