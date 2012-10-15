//
// AddParserActionHandler.ipp
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

#ifndef SWEET_PARSER_ADDHANDLER_IPP_INCLUDED
#define SWEET_PARSER_ADDHANDLER_IPP_INCLUDED

#include "AddParserActionHandler.hpp"
#include <sweet/assert/assert.hpp>

namespace sweet
{

namespace parser
{

/**
// Constructor.
//
// @param parser
//  The %Parser to add actions to (assumed not null).
*/
template <class Iterator, class UserData, class Char, class Traits, class Allocator>
AddParserActionHandler<Iterator, UserData, Char, Traits, Allocator>::AddParserActionHandler( Parser<Iterator, UserData, Char, Traits, Allocator>* parser )
: parser_( parser )
{
    SWEET_ASSERT( parser_ );
}

/**
// Set the function to call for the default action (taken on a reduction when 
// no action is specified in the grammar).
//
// @param function
//  The function to call for the default action.
//
// @return
//  This %AddParserActionHandler.
*/
template <class Iterator, class UserData, class Char, class Traits, class Allocator>
const AddParserActionHandler<Iterator, UserData, Char, Traits, Allocator>& 
AddParserActionHandler<Iterator, UserData, Char, Traits, Allocator>::default_action( ParserActionFunction function ) const
{
    SWEET_ASSERT( parser_ );
    parser_->set_default_action_handler( function );
    return *this;
}

/**
// Set the function to call when the %parser action \e identifier is taken.
//
// @param identifier
//  The identifier of the %parser action to assign a function to (matches the
//  identifier specified between '[' and ']' characters at the end of a
//  production).
//
// @param function
//  The function to call when the %parser action needs to be taken.
//
// @return
//  This AddParserActionHandler.
*/
template <class Iterator, class UserData, class Char, class Traits, class Allocator>
const AddParserActionHandler<Iterator, UserData, Char, Traits, Allocator>& 
AddParserActionHandler<Iterator, UserData, Char, Traits, Allocator>::operator()( const char* identifier, ParserActionFunction function ) const
{
    SWEET_ASSERT( identifier );
    SWEET_ASSERT( parser_ );
    parser_->set_action_handler( identifier, function );
    return *this;
}

}

}

#endif
