//
// TestParsers.cpp
// Copyright (c) 2009 - 2011 Charles Baker.  All rights reserved.
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

#include "stdafx.hpp"
#include <sweet/parser/ParserStateMachine.hpp>
#include <sweet/parser/ParserErrorPolicy.hpp>
#include <sweet/parser/Error.hpp>
#include <sweet/unit/UnitTest.h>
#include <stdio.h>
#include <string.h>

using namespace sweet;
using namespace sweet::parser;

SUITE( PrecedenceDirectives )
{
    TEST( ExpressionsThatRequireShiftReduceConflictResolution )
    {
        struct EventSink : public ParserErrorPolicy
        {    
            int errors_;
            
            EventSink ()
            : errors_( 0 )
            {
            }

            void parser_error( int line, const error::Error& error )
            {
                ++errors_;
                printf( "%s\n", error.what() );
                CHECK( error.error() == PARSER_ERROR_PARSE_TABLE_CONFLICT );
            }
        };

        const char* grammar = 
            "ExpressionsThatRequireShiftReduceConflictResolution {\n"
            " \n"
            "   %whitespace \"[ \t\r\n]*\";\n"
            "   %left '+' '-'; \n"
            "   %left '*' '/'; \n"
            "   %none integer; \n"
            " \n"
            "   unit: expr;\n"
            "   expr: expr '+' expr \n"
            "       | expr '-' expr \n"
            "       | expr '*' expr \n"
            "       | expr '/' expr \n"
            "       | integer \n"
            "       ; \n"
            "   integer: \"[0-9]+\"; \n"
            "}"
        ;
        
        EventSink event_sink;
        ParserStateMachine parser_state_machine( grammar, grammar + strlen(grammar), &event_sink );
        CHECK( event_sink.errors_ == 0 );
    }
}
