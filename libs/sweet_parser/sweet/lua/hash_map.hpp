//
// hash_map.hpp
// Copyright (c) 2007  - 2010 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_HASH_MAP_HPP_INCLUDED
#define SWEET_LUA_HASH_MAP_HPP_INCLUDED

#include <hash_map>

namespace sweet
{

namespace lua
{

/**
// @internal
//
// Convert stdext::hash_maps that are pushed onto the Lua stack into Lua iterator
// functions.
//
// This doesn't push the stdext::hash_map itself onto the stack - the application
// is responsible for making sure that the stdext::hash_map is allocated for at 
// least as long as the Lua iterator function is being used.
//
// @param lua_state
//  The lua_State to push the iterator function onto the stack of.
//
// @param value
//  The stdext::hash_map to iterate over.
*/
template <class Key, class Data, class Traits, class Allocator>
struct LuaConverter<const stdext::hash_map<Key, Data, Traits, Allocator>&>
{
    static void push( lua_State* lua_state, const stdext::hash_map<Key, Data, Traits, Allocator>& value )
    {
        lua_push( lua_state, value.begin(), value.end() );
    }
};

}

}

#endif
