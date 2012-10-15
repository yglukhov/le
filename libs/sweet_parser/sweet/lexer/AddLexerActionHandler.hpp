//
// AddLexerActionHandler.hpp
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

#ifndef SWEET_LEXER_ADDLEXERACTIONHANDLER_HPP_INCLUDED
#define SWEET_LEXER_ADDLEXERACTIONHANDLER_HPP_INCLUDED

#include <functional>

namespace sweet
{

namespace lexer
{

template <class Iterator, class Char, class Traits, class Allocator> class Lexer;

/**
// A helper that provides a convenient syntax for adding handlers to a %Lexer.
*/
template <class Iterator, class Char, class Traits, class Allocator>
class AddLexerActionHandler
{
    typedef std::tr1::function<void (Iterator* begin, Iterator end, std::basic_string<Char, Traits, Allocator>* lexeme, const void** symbol)> LexerActionFunction;

    Lexer<Iterator, Char, Traits, Allocator>* lexer_; ///< The Lexer to add handlers to.

    public:
        AddLexerActionHandler( Lexer<Iterator, Char, Traits, Allocator>* lexer );
        const AddLexerActionHandler& operator()( const char* identifier, LexerActionFunction function ) const;
};

}

}

#endif
