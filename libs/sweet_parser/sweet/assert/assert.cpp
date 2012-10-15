//
// assert.cpp
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

#include "stdafx.hpp"
#include "assert.hpp"
#include <sweet/build.hpp>
#include <stdlib.h>
#include <stdio.h>

#if defined(BUILD_OS_WINDOWS)
#include <windows.h>
#endif

namespace sweet
{

namespace assert
{

/**
// Break in the debugger.
*/
void sweet_break()
{
#if defined(BUILD_OS_WINDOWS)
    DebugBreak();
#endif
}

/**
// If \e expression isn't true then print \e file, \e line, and 
// \e description to the debug console and stderr.
//
// @param expression
//  The expression that has failed the assertion.
//
// @param file
//  The source file that the failed assertion is in.
//
// @param line
//  The line number that the failed assertion is on.
*/
void sweet_assert( bool expression, const char* description, const char* file, int line )
{
#if defined(BUILD_OS_WINDOWS)
    int error = ::GetLastError();
    if ( !expression )
    {
        char message [1024];
        _snprintf( message, sizeof(message), "%s(%i) : %s\n", file, line, description );
        message[sizeof(message) - 1] = 0;
        ::fputs( message, stderr );
    }
    ::SetLastError( error );
#endif
}

}

}
