//
// filesystem.hpp
// Copyright (c) 2007 - 2012 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_FILESYSTEM_HPP_INCLUDED
#define SWEET_LUA_FILESYSTEM_HPP_INCLUDED

#include <boost/filesystem.hpp>

namespace sweet
{

namespace lua
{

/**
// @internal
//
// Convert boost::filesystem::basic_directory_entries that are pushed onto
// the Lua stack into strings.
//
// @todo
//  Pushing a boost::filesystem::basic_directory_entry is currently templated
//  on the type of path (allowing different character types) even though only 
//  narrow character strings have been considered.
*/
template <class Path>
struct LuaConverter<boost::filesystem::basic_directory_entry<Path> >
{
    /**
    // @internal
    //
    // @param lua
    //  The lua_State to push the string onto the stack of.
    //
    // @param value
    //  The boost::filesystem::basic_directory_entry to push.
    */
    static void push( lua_State* lua_state, const boost::filesystem::basic_directory_entry<Path>& entry  )
    {
        SWEET_ASSERT( lua_state != NULL );
        lua_pushlstring( lua_state, entry.path().string().c_str(), entry.path().string().length() );
    }
};



/**
// @internal
//
// Convert boost::filesystem::basic_directory_iterators that are pushed onto 
// the Lua stack into Lua iterator functions.
//
// This pushes an iterator that will iterator from the 
// basic_directory_iterator specified by \e value to the default constructed
// basic_directory_iterator.
//
// @todo
//  Pushing a boost::filesystem::basic_directory_iterator is currently 
//  templated on the type of path (allowing different character types) even 
//  though only narrow character strings have been considered.
//
// @param lua
//  The lua_State to push the iterator function onto the stack of.
//
// @param value
//  The boost::filesystem::basic_directory_iterator to begin the iteration at.
*/
template <class Path>
struct LuaConverter<boost::filesystem::basic_directory_iterator<Path> >
{
    static void push( lua_State* lua_state, const boost::filesystem::basic_directory_iterator<Path>& value )
    {
        lua_push_iterator( lua_state, value, boost::filesystem::basic_directory_iterator<Path>() );
    }

    static const boost::filesystem::basic_directory_iterator<Path>& to( lua_State* lua_state, int position )
    {
        return lua_to_value<boost::filesystem::basic_directory_iterator<Path> >( lua_state, position );
    }
};


/**
// @internal
//
// Convert boost::filesystem::basic_recursive_directory_iterators that are 
// pushed onto the Lua stack into Lua iterator functions.
//
// This pushes an iterator that will iterate from the 
// basic_recursive_directory_iterator specified by \e value to the default 
// constructed basic_recursive_directory_iterator that marks the end of the
// iteration.
//
// @todo
//  Pushing a boost::filesystem::basic_recursive_directory_iterator is 
//  currently templated on the type of path (allowing different character 
//  types) even though only narrow character strings have been considered.
//
// @param lua_state
//  The lua_State to push the iterator function onto the stack of.
//
// @param value
//  The boost::filesystem::basic_directory_iterator to begin the iteration at.
*/
template <class Path>
struct LuaConverter<boost::filesystem::basic_recursive_directory_iterator<Path> >
{
    static void push( lua_State* lua_state, const boost::filesystem::basic_recursive_directory_iterator<Path>& value )
    {
        lua_push_iterator( lua_state, value, boost::filesystem::basic_recursive_directory_iterator<Path>() );
    }

    static const boost::filesystem::basic_recursive_directory_iterator<Path>& to( lua_State* lua_state, int position )
    {
        return lua_to_value<boost::filesystem::basic_recursive_directory_iterator<Path> >( lua_state, position );
    }
};

}

}

#endif
