//
// LexerErrorPolicy.hpp
// Copyright (c) 2010 - 2011 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LEXER_LEXERERRORPOLICY_HPP_INCLUDED
#define SWEET_LEXER_LEXERERRORPOLICY_HPP_INCLUDED

#include "declspec.hpp"
#include <stdarg.h>

namespace sweet
{

namespace error
{

class Error;

}

namespace lexer
{

/**
// An interface to be implemented by classes that wish to handle errors and 
// %debug information from the %lexer library.
*/
class SWEET_LEXER_DECLSPEC LexerErrorPolicy
{
    public:
        virtual ~LexerErrorPolicy();
        virtual void lexer_error( int line, const error::Error& error );
        virtual void lexer_vprintf( const char* format, va_list args );
};

}

}

#endif