//
// LexerLexerTransition.cpp
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
#include "LexerTransition.hpp"
#include "LexerAction.hpp"
#include "LexerState.hpp"
#include <sweet/assert/assert.hpp>
#include <stdio.h>

using namespace sweet::lexer;

#if defined(BUILD_PLATFORM_MSVC)
#define snprintf _snprintf
#endif

/**
// Constructor.
//
// @param begin
//  The first character in the interval that this transition can be taken on.
//
// @param end
//  One past the last character in the interval that this transition can be 
//  taken on.
//
// @param state
//  The state that is transitioned to (assumed not null).
//
// @param action
//  The action to take when this transition is taken or null if this 
//  transition doesn't take an action.
*/
LexerTransition::LexerTransition( int begin, int end, const LexerState* state, const LexerAction* action )
: begin_( begin ),
  end_( end ),
  state_( state ),
  action_( action )
{
    SWEET_ASSERT( begin_ < end_ );
    SWEET_ASSERT( state_ );
}

/**
// Is this transition taken on \e character?
//
// @return
//  True if this transition is taken on character otherwise false.
*/
bool LexerTransition::is_on_character( int character ) const
{
    return character >= begin_ && character < end_;
}

/**
// Get the first character in the interval that this transition can be taken 
// on.
//
// @return
//  The first character.
*/
int LexerTransition::get_begin() const
{
    return begin_;
}

/**
// Get the character that is one past the last character in the interval 
// that this transition can be taken on.
//
// @return
//  The last character.
*/
int LexerTransition::get_end() const
{
    return end_;
}

/**
// Get the action that is taken when this transition is taken.
//
// @return
//  The action or null if this transition doesn't have an action.
*/
const LexerAction* LexerTransition::get_action() const
{
    return action_;
}

/**
// Get the state that this transition is to.
//
// @return
//  The state.
*/
const LexerState* LexerTransition::get_state() const
{
    SWEET_ASSERT( state_ );
    return state_;
}

/**
// Describe this transition.
//
// @param description
//  A variable to receive the description of this transition (assumed not 
//  null).
*/
void LexerTransition::describe( std::string* description ) const
{
    SWEET_ASSERT( description );
    SWEET_ASSERT( state_ );    
    
    char buffer [512];
    snprintf( buffer, sizeof(buffer), "to %d on ['%c' %d, '%c' %d) %s", 
        state_->get_index(), 
        begin_ > 32 && begin_ < 128 ? begin_ : '.', 
        begin_, 
        end_ > 32 && end_ < 128 ? end_ : '.', 
        end_, 
        action_ ? action_->get_identifier().c_str() : ""
    );
    buffer [sizeof(buffer) - 1] = '\0';
    description->append( buffer );
}

/**
// Less than operator.
//
// @return
//  True if both the beginning and end of this transition's interval is less
//  than the beginning of \e transition's interval.
*/
bool LexerTransition::operator<( const LexerTransition& transition ) const
{
    return begin_ < transition.begin_ && end_ <= transition.begin_;
}
