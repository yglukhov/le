//
// AddLexerActionHandler.ipp
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

#ifndef SWEET_LEXER_ADDLEXERACTIONHANDLER_IPP_INCLUDED
#define SWEET_LEXER_ADDLEXERACTIONHANDLER_IPP_INCLUDED

#include "AddLexerActionHandler.hpp"
#include <sweet/assert/assert.hpp>

namespace sweet
{

namespace lexer
{

/**
// Constructor.
//
// @param lexer
//  The %Lexer to add actions to (assumed not null).
*/
template <class Iterator, class Char, class Traits, class Allocator>
AddLexerActionHandler<Iterator, Char, Traits, Allocator>::AddLexerActionHandler( Lexer<Iterator, Char, Traits, Allocator>* lexer )
: lexer_( lexer )
{
    SWEET_ASSERT( lexer_ );
}


/**
// Set the function to call when the lexer action \e identifier is taken.
//
// @param identifier
//  The identifier of the lexer action to assign a function to (matches the
//  identifier specified between ':' characters in a regular expression).
//
// @param function
//  The function to call when the lexer action needs to be taken.
//
// @return
//  This %AddLexerActionHandler.
*/
template <class Iterator, class Char, class Traits, class Allocator>
const AddLexerActionHandler<Iterator, Char, Traits, Allocator>& 
AddLexerActionHandler<Iterator, Char, Traits, Allocator>::operator()( const char* identifier, LexerActionFunction function ) const
{
    SWEET_ASSERT( identifier );
    SWEET_ASSERT( lexer_ );
    lexer_->set_action_handler( identifier, function );
    return *this;
}

}

}

#endif
