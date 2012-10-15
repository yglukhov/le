//
// LexerGenerator.hpp
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

#ifndef SWEET_LEXER_LEXERGENERATOR_HPP_INCLUDED
#define SWEET_LEXER_LEXERGENERATOR_HPP_INCLUDED

#include <sweet/pointer/ptr.hpp>
#include <sweet/pointer/ptr_less.hpp>
#include <sweet/lexer/LexerToken.hpp>
#include <vector>
#include <set>

namespace sweet
{

namespace error
{

class Error;

}

namespace lexer
{

class LexerState;
class LexerAction;
class LexerErrorPolicy;
class RegexParser;

/**
// @internal 
//
// Generate a lexical analyzer.
*/
class LexerGenerator
{
    LexerErrorPolicy*                               event_sink_;             ///< The event sink to report errors and debug information to or null to ignore errors and debug information.
    std::vector<ptr<LexerAction> >                   actions_;                ///< The lexical analyzer actions.
    std::set<ptr<LexerState>, ptr_less<LexerState> > states_;                 ///< The states generated for the lexical analyzer.
    std::set<ptr<LexerState>, ptr_less<LexerState> > whitespace_states_;      ///< The states generated for the whitespace lexical analyzer.
    const LexerState*                               start_state_;            ///< The starting state for the lexical analyzer.
    const LexerState*                               whitespace_start_state_; ///< The starting state for the whitespace lexical analyzer.
    std::vector<std::pair<int, bool> >               ranges_;                 ///< Ranges generated for the current transition while generating.

    public:
        LexerGenerator( const LexerToken& token, LexerErrorPolicy* event_sink );
        LexerGenerator( const std::vector<LexerToken>& tokens, const std::vector<LexerToken>& whitespace_tokens, LexerErrorPolicy* event_sink );

        std::vector<ptr<LexerAction> >& actions();
        std::set<ptr<LexerState>, ptr_less<LexerState> >& states();
        std::set<ptr<LexerState>, ptr_less<LexerState> >& whitespace_states();
        const LexerState* start_state() const;
        const LexerState* whitespace_start_state() const;
        const lexer::LexerAction* add_lexer_action( const std::string& identifier );

        void fire_error( int line, const error::Error& error ) const;
        void fire_printf( const char* format, ... ) const;

    private:
        ptr<LexerState> goto_( const LexerState* state, int begin, int end );
        void generate_states( const RegexParser& regular_expression_parser, std::set<ptr<LexerState>, ptr_less<LexerState> >* states, const LexerState** start_state );
        void generate_indices_for_states();
        void generate_symbol_for_state( LexerState* state ) const;

        void clear();
        void insert( int begin, int end );
};

}

}

#endif
