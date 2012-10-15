//
// ParserTransition.hpp
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

#ifndef SWEET_PARSER_PARSERTRANSITION_HPP_INCLUDED
#define SWEET_PARSER_PARSERTRANSITION_HPP_INCLUDED

#include "declspec.hpp"
#include <string>
#include <set>

namespace sweet
{

namespace parser
{

class ParserState;
class ParserSymbol;
class ParserProduction;

/**
// The type of a transition in a parser's state machine.
*/
enum ParserTransitionType
{
    TRANSITION_SHIFT, ///< Shift a terminal symbol onto the parser's stack.
    TRANSITION_REDUCE ///< Reduce one or more symbols on the parser's stack into a non terminal.
};

/**
// A transition in a parser's state machine.
*/
class SWEET_PARSER_DECLSPEC ParserTransition
{
    public:
        static const int INVALID_INDEX = -1;

    private:
        const ParserSymbol* symbol_; ///< The symbol that the transition is taken on.
        mutable ParserState* state_; ///< The state that is transitioned to.
        mutable const ParserProduction* reduced_production_; ///< The production that is reduced on this transition or null if there is no reduction.
        mutable ParserTransitionType type_; ///< The type of transition that this is.
        mutable int index_; ///< The index of this transition.

    public:
        ParserTransition( const ParserSymbol* symbol, ParserState* state );
        ParserTransition( const ParserSymbol* symbol, const ParserProduction* reduced_production );

        int get_type() const;
        ParserState* get_state() const;
        const ParserProduction* get_reduced_production() const;
        bool is_symbol( const ParserSymbol* symbol ) const;
        const ParserSymbol* get_symbol() const;
        void describe( std::string* description ) const;
        
        void set_index( int index ) const;
        int get_index() const;
        
        void override_shift_to_reduce( const ParserProduction* reduced_production ) const;
        void override_reduce_to_reduce( const ParserProduction* reduced_production ) const;
        
        bool operator<( const ParserTransition& transition ) const;
};

}

}

#endif
