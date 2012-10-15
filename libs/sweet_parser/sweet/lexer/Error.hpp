//
// Error.hpp
// Copyright (c) 2007 - 2011 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LEXER_ERROR_HPP_INCLUDED
#define SWEET_LEXER_ERROR_HPP_INCLUDED

#include "declspec.hpp"
#include <sweet/error/Error.hpp>
#include <sweet/error/ErrorTemplate.hpp>

namespace sweet
{

namespace lexer
{

/**
// Unique identifiers for the errors thrown from the %parser library.
//
// @relates Error
*/
enum ErrorCode
{
    LEXER_ERROR_NONE,            ///< No %error.
    LEXER_ERROR_SYNTAX,          ///< Syntax %error occured while parsing some input.
    LEXER_ERROR_SYMBOL_CONFLICT, ///< A lexer state matches more than one symbol.
    LEXER_ERROR_LEXICAL_ERROR    ///< A lexical error occured while scanning an input sequence.
};

/**
// Errors thrown from the %lexer library.
*/
class SWEET_LEXER_DECLSPEC Error : public error::Error
{
    public:
        Error( int error );
};

/**
// Syntax %error.
//
// @relates Error
*/
typedef error::ErrorTemplate<LEXER_ERROR_SYNTAX, Error> SyntaxError;

/**
// A lexer state matches more than one symbol.
//
// @relates Error
*/
typedef error::ErrorTemplate<LEXER_ERROR_SYMBOL_CONFLICT, Error> LexerSymbolConflictError;

/**
// A lexical error occured while scanning an input sequence.
//
// @relates Error
*/
typedef error::ErrorTemplate<LEXER_ERROR_LEXICAL_ERROR, Error> LexerLexicalError;

}

}

#endif
