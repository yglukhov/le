//
// ParserState.hpp
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

#ifndef SWEET_PARSER_PARSERSTATE_HPP_INCLUDED
#define SWEET_PARSER_PARSERSTATE_HPP_INCLUDED

#include "declspec.hpp"
#include "ParserItem.hpp"
#include "ParserTransition.hpp"
#include <set>

namespace sweet
{

namespace parser
{

/**
// A state in a parser's state machine.
*/
class SWEET_PARSER_DECLSPEC ParserState
{
    public:
        static const int INVALID_INDEX = -1;

    private:
        std::set<ParserItem> items_; ///< The items that define the positions within the grammar that this state represents.
        std::set<ParserTransition> transitions_; ///< The available transitions from this state.
        bool processed_; ///< True if this state has been processed during state machine generation otherwise false.
        int index_; ///< The index of this state.

    public:
        ParserState();

        int add_item( ptr<ParserProduction> production, int position );
        int add_lookahead_symbols( ptr<ParserProduction> production, int position, const std::set<const ParserSymbol*>& lookahead_symbols );
        const std::set<ParserItem>& get_items() const;
        void describe( std::string* description ) const;
        std::string description() const;

        void add_transition( const ParserSymbol* symbol, ParserState* state );
        void add_transition( const ParserSymbol* symbol, const ParserProduction* production );
        void add_transition( const std::set<const ParserSymbol*>& symbols, const ParserProduction* production );
        void generate_indices_for_transitions();
        ParserTransition* find_transition_by_symbol( const ParserSymbol* symbol );
        const ParserTransition* find_transition_by_symbol( const ParserSymbol* symbol ) const;
        const std::set<ParserTransition>& get_transitions() const;

        void set_processed( bool processed );
        bool is_processed() const;

        void set_index( int index );
        int get_index() const;

        bool operator<( const ParserState& state ) const;
};

}

}

#endif
