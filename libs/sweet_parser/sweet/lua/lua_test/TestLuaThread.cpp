//
// TestLuaObject.cpp
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

#include <sweet/unit/UnitTest.h>
#include <sweet/lua/Lua.hpp>
#include <sweet/lua/LuaObject.hpp>
#include <sweet/lua/LuaThread.hpp>

using namespace sweet::lua;

SUITE( TestLuaThread )
{
    struct Fixture
    {
        Lua       lua;
        LuaThread lua_thread;
        LuaObject lua_object;

        Fixture()
        : lua(),
          lua_thread( lua ),
          lua_object( lua )
        {
            lua.globals()
                ( "lua_object", lua_object                      )
                ( "yield",      yield(&Fixture::yield_function) )
            ;
        }

        static void yield_function() {};
    };

    TEST_FIXTURE( Fixture, TestImport )
    {
        const char SCRIPT[] = "function add( a, b ) return a + b; end";
        lua_thread.call( SCRIPT, SCRIPT + sizeof(SCRIPT) - 1, "TestImport" ).end();

        int result = 0;
        lua_thread.call( "add" )
            ( 1 )( 2 )
        .end( &result );
        CHECK( result == 1 + 2 );
    }

    TEST_FIXTURE( Fixture, TestCallFunction )
    {
        const char SCRIPT[] = "function bool_function() return true; end;";
        lua_thread.call( SCRIPT, SCRIPT + sizeof(SCRIPT) - 1, "TestCallFunction" ).end();

        bool result = false;
        lua_thread.call( "bool_function" ).end( &result );
        CHECK( result );
    }

    TEST_FIXTURE( Fixture, TestCallMemberFunction )
    {
        const char SCRIPT[] = "function lua_object:bool_function() return true; end;";
        lua.call( SCRIPT, SCRIPT + sizeof(SCRIPT) - 1, "TestCallMemberFunction" ).end();

        bool result = false;
        lua_thread.call<LuaObject>( "bool_function", lua_object ).end( &result );
        CHECK( result );
    }

    TEST_FIXTURE( Fixture, TestResumeFunction )
    {
        const char SCRIPT[] = "function resume_function() yield(); yield(); return true; end;";
        lua.call( SCRIPT, SCRIPT + sizeof(SCRIPT) - 1, "TestResumeFunction" ).end();

        lua_thread.resume( "resume_function" ).end();
        CHECK( lua_thread.get_state() == LUA_THREAD_SUSPENDED );

        lua_thread.resume().end();
        CHECK( lua_thread.get_state() == LUA_THREAD_SUSPENDED );

        bool result = false;
        lua_thread.resume().end( &result );
        CHECK( result );        
    }

    TEST_FIXTURE( Fixture, TestResumeMemberFunction )
    {
        const char SCRIPT[] = "function lua_object:resume_function() yield(); yield(); return true; end;";
        lua.call( SCRIPT, SCRIPT + sizeof(SCRIPT) - 1, "TestResumeFunction" ).end();

        lua_thread.resume<LuaObject>( "resume_function", lua_object ).end();
        CHECK( lua_thread.get_state() == LUA_THREAD_SUSPENDED );

        lua_thread.resume().end();
        CHECK( lua_thread.get_state() == LUA_THREAD_SUSPENDED );

        bool result = false;
        lua_thread.resume().end( &result );
        CHECK( result );        
    }
}
