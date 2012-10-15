//
// TestLuaPreprocessor.cpp
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
#include <string.h>

using namespace sweet::lua;

SUITE( TestLuaPreprocessor )
{
    struct Fixture
    {
        Lua lua;
        
        Fixture()
        {
            const char* script = "io.write = print;";
            lua.globals()( "print", &Fixture::print );
            lua.call( script, script + strlen(script), "TestLuaPreprocessor" ).end();
        }
        
        static void print()
        {            
        }
    };

    TEST_FIXTURE( Fixture, HelloWorld )
    {
        const char* script = "<?lua for i = 1, 8 do ?>Hello World <?lua print(i) end ?>";
        lua.preprocess( script, script + strlen(script), "HelloWorld" ).end();
    }
    
    TEST_FIXTURE( Fixture, Expression )
    {
        const char* script = "<?lua= 'Hello World' ?>";
        lua.preprocess( script, script + strlen(script), "Expression" ).end();
        script = "<?lua= 32 ?>";
        lua.preprocess( script, script + strlen(script), "Expression" ).end();
    }
    
    TEST_FIXTURE( Fixture, EmbeddedPostLiteralSequence )
    {
        const char* script = "Embedded post literal ']])'";
        lua.preprocess( script, script + strlen(script), "EmbeddedPostLiteralSequence" ).end();
    }
    
    TEST_FIXTURE( Fixture, EmbeddedPostExpressionSequence )
    {
        const char* script = "<?lua= 'Embedded post expression ))' ?>";
        lua.preprocess( script, script + strlen(script), "EmbeddedPostExpressionSequence" ).end();
    }
}
