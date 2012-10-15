//
// LexerStateMachine.hpp
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

#ifndef SWEET_LEXER_LEXERSTATEMACHINE_HPP_INCLUDED
#define SWEET_LEXER_LEXERSTATEMACHINE_HPP_INCLUDED

#include "declspec.hpp"
#include <sweet/pointer/ptr.hpp>
#include <sweet/pointer/ptr_less.hpp>
#include <string>
#include <vector>
#include "LexerToken.hpp"

namespace sweet
{

namespace lexer
{

class LexerAction;
class LexerState;
class LexerErrorPolicy;

/**
// The data that defines the state machine for a lexical analyzer.
*/
class SWEET_LEXER_DECLSPEC LexerStateMachine
{
    std::string identifier_; ///< The identifier of this LexerStateMachine.
    std::vector<ptr<lexer::LexerAction> > actions_; ///< The lexer actions for this ParserStateMachine.
    std::vector<ptr<LexerState> > states_; ///< The states that make up the state machine for this LexerStateMachine.
    std::vector<ptr<LexerState> > whitespace_states_; ///< The states that make up the state machine for whitespace in this LexerStateMachine.
    const LexerState* start_state_; ///< The starting state for the state machine.
    const LexerState* whitespace_start_state_; ///< The starting state for the whitespace state machine.

    public:
        LexerStateMachine( const std::string& regular_expression, void* symbol, LexerErrorPolicy* event_sink = NULL );
        LexerStateMachine( const std::string& identifier, const std::vector<LexerToken>& tokens, const std::vector<LexerToken>& whitespace_tokens = std::vector<LexerToken>(), LexerErrorPolicy* event_sink = NULL );

        const std::string& identifier() const;
        const std::vector<ptr<LexerAction> >& actions() const;
        const std::vector<ptr<LexerState> >& states() const;
        const std::vector<ptr<LexerState> >& whitespace_states() const;
        const LexerState* start_state() const;
        const LexerState* whitespace_start_state() const;
        void describe( std::string* description ) const;
        std::string description() const;
};

}

}

#endif
