//
// AddParserActionHandler.hpp
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

#ifndef SWEET_PARSER_ADDHANDLER_HPP_INCLUDED
#define SWEET_PARSER_ADDHANDLER_HPP_INCLUDED

#if defined(BUILD_PLATFORM_MSVC) || 1
#include <functional>
#else
#include <tr1/functional>
#endif

namespace sweet
{

namespace parser
{

class ParserSymbol;
template <class Iterator, class UserData, class Char, class Traits, class Allocator> class Parser;

/**
// A helper that provides a convenient syntax for adding handlers to a %Parser.
*/
template <class Iterator, class UserData, class Char, class Traits, class Allocator>
class AddParserActionHandler
{
    typedef std::tr1::function<void (Iterator* begin, Iterator end, std::basic_string<Char, Traits, Allocator>* lexeme, const ParserSymbol** symbol)> LexerActionFunction;
    typedef std::tr1::function<UserData (const ParserSymbol* symbol, const ParserNode<UserData, Char, Traits, Allocator>* start, const ParserNode<UserData, Char, Traits, Allocator>* finish)> ParserActionFunction;

    Parser<Iterator, UserData, Char, Traits, Allocator>* parser_; ///< The Parser to add handlers to.

    public:
        AddParserActionHandler( Parser<Iterator, UserData, Char, Traits, Allocator>* parser );
        const AddParserActionHandler& default_action( ParserActionFunction function ) const;
        const AddParserActionHandler& operator()( const char* identifier, ParserActionFunction function ) const;
};

}

}

#endif
