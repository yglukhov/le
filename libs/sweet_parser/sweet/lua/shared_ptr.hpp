//
// shared_ptr.hpp
// Copyright (c) 2009 - 2010 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_SHARED_PTR_HPP_INCLUDED
#define SWEET_LUA_SHARED_PTR_HPP_INCLUDED

#include <sweet/build.hpp>
#include <boost/shared_ptr.hpp>
#include <sweet/traits/shared_ptr.hpp>

namespace sweet
{

namespace lua
{

template <class Type>
struct LuaObjectConverter<boost::shared_ptr<Type>, LuaByReference>
{
    static void create( lua_State* lua_state, boost::shared_ptr<Type> value )
    {
        lua_create_object( lua_state, const_cast<Type*>(value.get()) );
    }

    static void destroy( lua_State* lua_state, boost::shared_ptr<Type> value )
    {
        lua_destroy_object( lua_state, const_cast<Type*>(value.get()) );
    }
    
    static void weaken( lua_State* lua_state, boost::shared_ptr<Type> value )
    {
        lua_weaken_object( lua_state, const_cast<Type*>(value.get()) );
    }

    static void push( lua_State* lua_state, boost::shared_ptr<Type> value )
    {
        lua_push_object( lua_state, const_cast<Type*>(value.get()) );
    }
    
    static boost::shared_ptr<Type> to( lua_State* lua_state, int position )
    {
        SWEET_ASSERT( lua_state != NULL );

        boost::shared_ptr<Type> value;

        if ( !lua_isnoneornil(lua_state, position) )
        {
            LuaStackGuard guard( lua_state );
            lua_validate_type( lua_state, position, SWEET_STATIC_TYPEID(Type) );
            lua_getfield( lua_state, position, lua::PTR_KEYWORD );
            SWEET_ASSERT( lua_isuserdata(lua_state, -1) );
            value = lua_to_value<boost::shared_ptr<Type>>( lua_state, -1 );
        }

        return value;
    }
};

template <class Type>
void lua_push( lua_State* lua_state, boost::shared_ptr<Type> value )
{    
    typedef traits::traits<Type>::base_type base_type;
    LuaObjectConverter<boost::shared_ptr<Type>, LuaTraits<base_type>::storage_type>::push( lua_state, value );
}

template <class Type>
struct LuaObjectConverter<boost::weak_ptr<Type>, LuaByReference>
{
    static void create( lua_State* lua_state, boost::weak_ptr<Type> weak_value )
    {
        boost::shared_ptr<Type> value( weak_value );
        lua_create_object( lua_state, const_cast<Type*>(value.get()) );
    }

    static void destroy( lua_State* lua_state, boost::weak_ptr<Type> weak_value )
    {
        boost::shared_ptr<Type> value( weak_value );
        lua_destroy_object( lua_state, const_cast<Type*>(value.get()) );
    }

    static void weaken( lua_State* lua_state, boost::weak_ptr<Type> weak_value )
    {
        boost::shared_ptr<Type> value( weak_value );
        lua_weaken_object( lua_state, const_cast<Type*>(value.get()) );
    }

    static void push( lua_State* lua_state, boost::weak_ptr<Type> weak_value )
    {
        boost::shared_ptr<Type> value( weak_value );
        lua_push_object( lua_state, const_cast<Type*>(value.get()) );
    }
    
    static boost::weak_ptr<Type> to( lua_State* lua_state, int position )
    {
        SWEET_ASSERT( lua_state != NULL );

        boost::weak_ptr<Type> weak_value;

        if ( !lua_isnoneornil(lua_state, position) )
        {
            LuaStackGuard guard( lua_state );
            lua_validate_type( lua_state, position, SWEET_STATIC_TYPEID(Type) );
            lua_getfield( lua_state, position, lua::PTR_KEYWORD );
            SWEET_ASSERT( lua_isuserdata(lua_state, -1) );
            weak_value = lua_to_value<boost::shared_ptr<Type>>( lua_state, -1 );
        }

        return weak_value;
    }
};

template <class Type>
void lua_push( lua_State* lua_state, boost::weak_ptr<Type> weak_value )
{    
    typedef traits::traits<Type>::base_type base_type;
    LuaObjectConverter<boost::weak_ptr<Type>, LuaTraits<base_type>::storage_type>::push( lua_state, weak_value );
}

}

}

#endif
