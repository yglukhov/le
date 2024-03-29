//
// LuaThread.hpp
// Copyright (c) 2008 - 2011 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_LUATHREAD_HPP_INCLUDED
#define SWEET_LUA_LUATHREAD_HPP_INCLUDED

#include "declspec.hpp"
#include "AddParameterHelper.ipp"
#include "AddGlobal.ipp"
#include "AddParameter.ipp"
#include "LuaInvoker.ipp"
#include "LuaReturner.ipp"
#include "lua_/lua.h"

namespace sweet
{

namespace lua
{

class Lua;
class LuaValue;

/**
// @internal
//
// The state of a %Lua thread.
*/
enum LuaThreadState
{
    LUA_THREAD_READY, // The LuaThread is ready to execute.
    LUA_THREAD_SUSPENDED, // The LuaThread has yielded while executing code.
    LUA_THREAD_ERROR // The LuaThread has errored while executing code. 
};

/**
// A %Lua coroutine.
*/
class SWEET_LUA_DECLSPEC LuaThread
{
    Lua* lua_; ///< The Lua virtual machine that this LuaThread is part of.
    lua_State* lua_state_; ///< The lua_State that represents this LuaThread.
    AddParameterHelper add_parameter_helper_; ///< The AddParameterHelper that stores state for AddParameters.

    public:
        LuaThread( Lua& lua );
        ~LuaThread();

        Lua* get_lua() const;
        lua_State* get_lua_state() const;
        LuaThreadState get_state() const;

        AddParameter call( lua_Reader reader, void* context, const char* name );
        AddParameter call( const char* filename, const char* name );
        AddParameter call( const char* first, const char* last, const char* name );
        AddParameter call( const char* function );
        AddParameter call( const LuaValue& function );
        template <class Type> AddParameter call( const char* function, const Type& object );

        AddParameter resume( const char* filename, const char* name );
        AddParameter resume( const char* first, const char* last, const char* name );
        AddParameter resume( const char* function );
        AddParameter resume( const LuaValue& function );
        template <class Type> AddParameter resume( const char* function, const Type& object );
        AddParameter resume();
};

}

}

#include "LuaThread.ipp"

#endif
