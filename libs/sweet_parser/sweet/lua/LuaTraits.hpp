//
// LuaTraits.hpp
// Copyright (c) 2009 - 2012 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_LUATRAITS_HPP_INCLUDED
#define SWEET_LUA_LUATRAITS_HPP_INCLUDED

/**
// The macro to define a LuaTraits class that associates a C++ type with its
// Lua storage type - LuaByValue, LuaByReference, or LuaWeakReference.
*/
#define SWEET_LUA_TYPE_CONVERSION( type, storage ) namespace sweet { namespace lua { template <> struct LuaTraits<type> { typedef lua::storage storage_type; }; } } 

namespace sweet
{

namespace lua
{

/**
// @internal
//
// A tag type used as a trait to specify that a type should be stored in the
// Lua virtual machine by value.
*/
struct LuaByValue {};

/**
// @internal
//
// A tag type used as a trait to specify that a type should be stored in the
// Lua virtual machine by reference.
*/
struct LuaByReference {};

/**
// @internal
//
// Extract trait information for Lua from types.
*/
template <class Type>
struct LuaTraits
{
    typedef LuaByValue storage_type;
};

class LuaObject;
template <>
struct LuaTraits<LuaObject>
{
    typedef LuaByReference storage_type;
};

}

}

#endif
