//
// LexerState.hpp
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

#ifndef SWEET_LEXER_LEXERSTATE_HPP_INCLUDED
#define SWEET_LEXER_LEXERSTATE_HPP_INCLUDED

#include "declspec.hpp"
#include "LexerItem.hpp"
#include "LexerTransition.hpp"
#include <string>
#include <set>

namespace sweet
{

namespace lexer
{

class RegexNode;

/**
// A state in a lexical analyzer's state machine.
*/
class SWEET_LEXER_DECLSPEC LexerState
{
    std::set<LexerItem>       items_;       ///< The items that define the positions within the regular expressions that this state represents.
    std::set<LexerTransition> transitions_; ///< The available transitions from this state to other states.
    const void*               symbol_;      ///< The symbol that this state recognizes or null if this state doesn't recognize a symbol.
    bool                      processed_;   ///< True if this state has been processed during state machine generation otherwise false.
    int                       index_;       ///< The index of this state.

    public:
        LexerState();

        int add_item( const std::set<RegexNode*, RegexNodeLess>& next_nodes );
        const std::set<LexerItem>& get_items() const;

        void add_transition( int begin, int end, LexerState* state );
        const LexerTransition* find_transition_by_character( int character ) const;
        const std::set<LexerTransition>& get_transitions() const;

        void set_symbol( const void* symbol );
        const void* get_symbol() const;

        void set_processed( bool processed );
        bool is_processed() const;

        void set_index( int index );
        int get_index() const;
        
        void describe( std::string* description ) const;
        bool operator<( const LexerState& state ) const;
};

}

}

#endif
