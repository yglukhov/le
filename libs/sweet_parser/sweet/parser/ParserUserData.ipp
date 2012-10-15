//
// ParserUserData.ipp
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

#ifndef SWEET_PARSER_PARSERUSERDATA_IPP_INCLUDED
#define SWEET_PARSER_PARSERUSERDATA_IPP_INCLUDED

#include "ParserUserData.hpp"
#include <sweet/assert/assert.hpp>

namespace sweet
{

namespace parser
{

/**
// Constructor.
//
// @param symbol
//  The symbol at this user data (assumed not null).
//
// @param lexeme
//  The lexeme at this user data.
*/
template <class Char, class Traits, class Allocator>
ParserUserData<Char, Traits, Allocator>::ParserUserData( const ParserSymbol* symbol, const std::basic_string<Char, Traits, Allocator>& lexeme )
: symbol_( symbol ),
  lexeme_( lexeme ),
  user_datas_()
{
    SWEET_ASSERT( symbol_ );
}

/**
// Constructor.
//
// @param symbol
//  The symbol at this user data (assumed not null).
//
// @param user_datas
//  The number of user datas that will be added as children of this user data.
*/
template <class Char, class Traits, class Allocator>
ParserUserData<Char, Traits, Allocator>::ParserUserData( const ParserSymbol* symbol, size_t user_datas )
: symbol_( symbol ),
  lexeme_(),
  user_datas_()
{
    SWEET_ASSERT( symbol_ );
    user_datas_.reserve( user_datas );
}

/**
// Constructor.
//
// @param symbol
//  The symbol at this user data.
//
// @param start
//  The first node to get user data from to add as a child of this user data.
//
// @param finish
//  One past the last node to get user data from to add as a child of this 
//  user data.
*/
template <class Char, class Traits, class Allocator>
ParserUserData<Char, Traits, Allocator>::ParserUserData( const ParserSymbol* symbol, const ParserNode* start, const ParserNode* finish )
: symbol_( symbol ),
  lexeme_(),
  user_datas_()
{
    SWEET_ASSERT( start );
    SWEET_ASSERT( finish );
    SWEET_ASSERT( start <= finish );
    SWEET_ASSERT( symbol_ );
    
    for ( const ParserNode* node = start; node != finish; ++node )
    {
        if ( node->get_user_data() )
        {
            user_datas_.push_back( node->get_user_data() );
        }
        else
        {
            ptr<ParserUserData<char> > user_data( new ParserUserData(node->get_symbol(), node->get_lexeme()) );
            user_datas_.push_back( user_data );
        }
    }
}

/**
// Get the symbol at this user data.
//
// @return
//  The symbol.
*/
template <class Char, class Traits, class Allocator>
const ParserSymbol* ParserUserData<Char, Traits, Allocator>::get_symbol() const
{
    return symbol_;
}

/**
// Get the lexeme at this user data.
//
// @return
//  The lexeme.
*/
template <class Char, class Traits, class Allocator>
const std::basic_string<Char, Traits, Allocator>& ParserUserData<Char, Traits, Allocator>::get_lexeme() const
{
    return lexeme_;
}

/**
// Append user data as a child of this user data.
//
// @param user_data
//  The user data to append to this user data.
*/
template <class Char, class Traits, class Allocator>
void ParserUserData<Char, Traits, Allocator>::append_user_data( ptr<ParserUserData> user_data )
{
    SWEET_ASSERT( std::find(user_datas_.begin(), user_datas_.end(), user_data) == user_datas_.end() );
    user_datas_.push_back( user_data );
}

/**
// Get the user datas that are part of this user data.
//
// @return
//  The user datas.
*/
template <class Char, class Traits, class Allocator>
const std::vector<ptr<ParserUserData<Char, Traits, Allocator> > >& ParserUserData<Char, Traits, Allocator>::get_user_datas() const
{
    return user_datas_;
}

}

}

#endif
