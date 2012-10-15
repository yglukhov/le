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

#ifndef SWEET_PARSER_ERROR_HPP_INCLUDED
#define SWEET_PARSER_ERROR_HPP_INCLUDED

#include "declspec.hpp"
#include <sweet/error/Error.hpp>
#include <sweet/error/ErrorTemplate.hpp>

namespace sweet
{

namespace parser
{

/**
// Unique identifiers for the errors thrown from the %parser library.
//
// @relates Error
*/
enum ErrorCode
{
    PARSER_ERROR_NONE, ///< No %error.
    PARSER_ERROR_OPENING_FILE_FAILED, ///< Opening a grammar file failed.
    PARSER_ERROR_PARSING_FAILED, ///< Parsing a grammar failed.
    PARSER_ERROR_UNEXPECTED, ///< An unexpected %error occured.
    PARSER_ERROR_SYNTAX, ///< Syntax %error occured while parsing some input.
    PARSER_ERROR_PARSE_TABLE_CONFLICT, ///< A shift-reduce or reduce-reduce conflict was found in the parse table.
    PARSER_ERROR_UNDEFINED_SYMBOL, ///< A grammar symbol is referenced but not defined.
    PARSER_ERROR_UNREFERENCED_SYMBOL, ///< A grammar symbol is defined but not referenced.
    PARSER_ERROR_ERROR_SYMBOL_ON_LEFT_HAND_SIDE ///< The 'error' symbol has been used on the left hand side of a production.
};

/**
// Errors thrown from the %parser library.
*/
class SWEET_PARSER_DECLSPEC Error : public error::Error
{
    public:
        Error( int error );
};

/**
// Opening a grammar file failed.
//
// @relates Error
*/
typedef error::ErrorTemplate<PARSER_ERROR_OPENING_FILE_FAILED, Error> OpeningFileFailedError;

/**
// Parsing a grammar file failed.
//
// @relates Error
*/
typedef error::ErrorTemplate<PARSER_ERROR_PARSING_FAILED, Error> ParsingFailedError;

/**
// An unexpected %error occured.
//
// @relates Error
*/
typedef error::ErrorTemplate<PARSER_ERROR_UNEXPECTED, Error> UnexpectedError;

/**
// Syntax %error.
//
// @relates Error
*/
typedef error::ErrorTemplate<PARSER_ERROR_SYNTAX, Error> SyntaxError;

/**
// A grammar symbol is referenced but not defined.
//
// @relates Error
*/
typedef error::ErrorTemplate<PARSER_ERROR_UNDEFINED_SYMBOL, Error> UndefinedSymbolError;

/**
// A shift-reduce or reduce-reduce conflict was found in the parse table.
//
// @relates Error
*/
typedef error::ErrorTemplate<PARSER_ERROR_PARSE_TABLE_CONFLICT, Error> ParseTableConflictError;

/**
// A grammar symbol is defined but not referenced.
//
// @relates Error
*/
typedef error::ErrorTemplate<PARSER_ERROR_UNREFERENCED_SYMBOL, Error> UnreferencedSymbolError;

/**
// The 'error' symbol has been used on the left hand side of a production.
//
// @relates Error
*/
typedef error::ErrorTemplate<PARSER_ERROR_ERROR_SYMBOL_ON_LEFT_HAND_SIDE, Error> ErrorSymbolOnLeftHandSideError;

}

}

#endif
