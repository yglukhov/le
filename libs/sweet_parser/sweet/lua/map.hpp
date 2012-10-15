//
// map.hpp
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

#ifndef SWEET_LUA_MAP_HPP_INCLUDED
#define SWEET_LUA_MAP_HPP_INCLUDED

#include <map>

namespace sweet
{

namespace lua
{

/**
// @internal
//
// Push std::pairs onto the Lua stack by pushing only the second value in
// the pair.
//
// @param lua_state
//  The lua_State to push the pair onto the stack of.
//
// @param value
//  The pair to push.
*/
template <class Key, class Data>
struct LuaConverter<const std::pair<Key, Data>&>
{
    static void push( lua_State* lua_state, const std::pair<Key, Data>& value )
    {
        lua_push( lua_state, value.second );
    }
};

/**
// @internal
//
// Convert std::maps that are pushed onto the Lua stack into Lua iterator
// functions.
//
// This doesn't push the std::map itself onto the stack - the application
// is responsible for making sure that the std::map is allocated for at 
// least as long as the Lua iterator function is being used.
//
// @param lua_state
//  The lua_State to push the iterator function onto the stack of.
//
// @param value
//  The std::map to iterate over.
*/
template <class Key, class Data, class Compare, class Allocator>
struct LuaConverter<const std::map<Key, Data, Compare, Allocator>&>
{
    static void push( lua_State* lua_state, const std::map<Key, Data, Compare, Allocator>& value )
    {
        lua_push_iterator( lua_state, value.begin(), value.end() );
    }
};

/**
// @internal
//
// Convert std::multimaps that are pushed onto the Lua stack into Lua iterator
// functions.
//
// This doesn't push the std::multimap itself onto the stack - the application
// is responsible for making sure that the std::multimap is allocated for at 
// least as long as the Lua iterator function is being used.
//
// @param lua_state
//  The lua_State to push the iterator function onto the stack of.
//
// @param value
//  The std::multimap to iterate over.
*/
template <class Key, class Data, class Compare, class Allocator>
struct LuaConverter<const std::multimap<Key, Data, Compare, Allocator>&>
{
    static void push( lua_State* lua_state, const std::multimap<Key, Data, Compare, Allocator>& value )
    {
        lua_push_iterator( lua_state, value.begin(), value.end() );
    }
};

}

}

#endif
