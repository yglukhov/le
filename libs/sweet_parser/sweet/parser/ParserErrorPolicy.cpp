//
// ParserErrorPolicy.cpp
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
#include "ParserErrorPolicy.hpp"

using namespace sweet;
using namespace sweet::parser;

/**
// Destructor.
*/
ParserErrorPolicy::~ParserErrorPolicy()
{
}

/**
// An %error has occured in a %ParserStateMachine.
//
// @param line
//  The line number that the %error occured on.
//
// @param error
//  The %Error that describes the %error that has occured.
*/
void 
ParserErrorPolicy::parser_error( int line, const error::Error& error )
{
}

/**
// Debug output has been sent from a %ParserStateMachine.
//
// @param format
//  The printf-style format string that describes the text to print.
//
// @param args
//  Arguments as described by \e format.
*/
void 
ParserErrorPolicy::parser_vprintf( const char* format, va_list args )
{
}
