//
// LuaYieldReturner.ipp
// Copyright (c) 2008  - 2010 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_LUA_LUAYIELDRETURNER_IPP_INCLUDED
#define SWEET_LUA_LUA_LUAYIELDRETURNER_IPP_INCLUDED

namespace sweet
{

namespace lua
{

/**
// Get the value to return to Lua at the end of a yielding call from Lua into 
// C++.
//
// @param lua_state
//  The lua_State that a call is being made from
//
// @return
//  Returns the value returned by lua_yield().
*/
template <class ReturnType>
int LuaYieldReturner<ReturnType>::return_value( lua_State* lua_state )
{
    SWEET_ASSERT( lua_state );
    return lua_yield( lua_state, 1 );
}

}

}

#endif
