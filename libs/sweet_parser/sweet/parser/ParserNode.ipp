//
// ParserNode.ipp
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

#ifndef SWEET_PARSER_PARSERNODE_IPP_INCLUDED
#define SWEET_PARSER_PARSERNODE_IPP_INCLUDED

#include "ParserNode.hpp"
#include <sweet/assert/assert.hpp>

namespace sweet
{

namespace parser
{

/**
// Constructor.
//
// @param state
//  The %ParserState at this node.
//
// @param started_productions
//  The productions that were started at this node.
//
// @param symbol
//  The Symbol at this node.
//
// @param user_data
//  The user data that stores application specific data at this node.
*/
template <class UserData, class Char, class Traits, class Allocator>
ParserNode<UserData, Char, Traits, Allocator>::ParserNode( const ParserState* state, const ParserSymbol* symbol, const UserData& user_data )
: state_( state ),
  symbol_( symbol ),
  lexeme_(),
  user_data_( user_data )
{
    SWEET_ASSERT( state );
}

/**
// Constructor.
//
// @param state
//  The state at this node.
//
// @param started_productions
//  The productions that were started at this node.
//
// @param symbol
//  The symbol at this node.
//
// @param lexeme
//  The lexeme at this node.
*/
template <class UserData, class Char, class Traits, class Allocator>
ParserNode<UserData, Char, Traits, Allocator>::ParserNode( const ParserState* state, const ParserSymbol* symbol, const std::basic_string<Char, Traits, Allocator>& lexeme )
: state_( state ),
  symbol_( symbol ),
  lexeme_( lexeme ),
  user_data_()
{
    SWEET_ASSERT( state );
}

/**
// Get the state at this node.
//
// @return
//  The state.
*/
template <class UserData, class Char, class Traits, class Allocator>
const ParserState* ParserNode<UserData, Char, Traits, Allocator>::get_state() const
{
    return state_;
}

/**
// Get the symbol at this state.
//
// @return
//  The symbol.
*/
template <class UserData, class Char, class Traits, class Allocator>
const ParserSymbol* ParserNode<UserData, Char, Traits, Allocator>::get_symbol() const
{
    return symbol_;
}

/**
// Get the lexeme at this state.
//
// @return
//  The lexeme.
*/
template <class UserData, class Char, class Traits, class Allocator>
const std::basic_string<Char, Traits, Allocator>& ParserNode<UserData, Char, Traits, Allocator>::get_lexeme() const
{
    return lexeme_;
}

/**
// Get the user data at this state.
//
// @return
//  The user data.
*/
template <class UserData, class Char, class Traits, class Allocator>
const UserData& ParserNode<UserData, Char, Traits, Allocator>::get_user_data() const
{
    return user_data_;
}

}

}

#endif
