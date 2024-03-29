//
// LuaObject.hpp
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

#ifndef SWEET_LUA_LUAOBJECT_HPP_INCLUDED
#define SWEET_LUA_LUAOBJECT_HPP_INCLUDED

#include "declspec.hpp"
#include "AddMember.hpp"
#include <string>

namespace sweet
{

namespace lua
{

class Lua;

/**
// A %Lua object table.
*/
class SWEET_LUA_DECLSPEC LuaObject
{
    Lua* lua_; ///< The %Lua object that this %LuaObject is part of.
    
    public:
        LuaObject();
        LuaObject( Lua& lua );
        ~LuaObject();

        AddMember members();
        bool is_value( const char* field ) const;
        bool is_boolean( const char* field ) const;
        bool is_number( const char* field ) const;
        bool is_string( const char* field ) const;
        bool is_function( const char* field ) const;
        bool boolean( const char* field ) const;
        int integer( const char* field ) const;
        float number( const char* field ) const;
        std::string string( const char* field ) const;

        template <class Archive> void persist( Archive& archive );

    private:
        LuaObject( const LuaObject& lua_object );
        LuaObject& operator=( const LuaObject& lua_object );
};

}

}

#endif
