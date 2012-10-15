//
// ParserGenerator.hpp
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

#ifndef PARSERGENERATOR_HPP_INCLUDED
#define PARSERGENERATOR_HPP_INCLUDED

#include <sweet/pointer/ptr.hpp>
#include <sweet/pointer/ptr_less.hpp>
#include <set>
#include <vector>
#include <string>

namespace sweet
{

namespace error
{

class Error;

}

namespace lexer
{

class LexerStateMachine;
class LexerErrorPolicy;

}

namespace parser
{

class ParserErrorPolicy;
class ParserAction;
class ParserSymbol;
class ParserItem;
class ParserState;
class ParserProduction;
class ParserGrammar;
class GrammarParser;

/**
// @internal
//
// %Parser state machine generator.
*/
class ParserGenerator
{
    ParserErrorPolicy* error_policy_; ///< The event sink to report errors to and print with or null to ignore errors and prints.
    std::string identifier_; ///< The identifier of the parser.
    std::vector<ptr<ParserAction> > actions_; ///< The actions in the parser.
    std::vector<ptr<ParserProduction> > productions_; ///< The productions in the parser.
    std::vector<ptr<ParserSymbol> > symbols_; ///< The symbols in the parser.
    std::set<ptr<ParserState>, ptr_less<ParserState> > states_; ///< The states in the parser's state machine.
    const ParserSymbol* start_symbol_; ///< The start symbol.
    const ParserSymbol* end_symbol_; ///< The end symbol.
    const ParserSymbol* error_symbol_; ///< The error symbol.
    ParserState* start_state_; ///< The start state.
    int errors_; ///< The number of errors that occured during parsing and generation.

    public:
        ParserGenerator( ParserGrammar& grammar, ParserErrorPolicy* error_policy );

        std::string& identifier();
        std::vector<ptr<ParserAction> >& actions();
        std::vector<ptr<ParserProduction> >& productions();
        std::vector<ptr<ParserSymbol> >& symbols();
        std::set<ptr<ParserState>, ptr_less<ParserState> >& states();
        const ParserSymbol* start_symbol();
        const ParserSymbol* end_symbol();
        const ParserSymbol* error_symbol();
        ParserState* start_state();
        int errors() const;

        void fire_error( int line, const error::Error& error );
        void fire_printf( const char* format, ... ) const;
                
    private:
        void generate( ParserGrammar& grammar );
        std::set<const ParserSymbol*> lookahead( const ParserItem& item ) const;
        void closure( const ptr<ParserState>& state );
        ptr<ParserState> goto_( const ptr<ParserState>& state, const ParserSymbol& symbol );
        int lookahead_closure( ParserState* state ) const;
        int lookahead_goto( ParserState* state ) const;
        void generate_states( const ParserSymbol* start_symbol, const ParserSymbol* end_symbol, const std::vector<ptr<ParserSymbol> >& symbols );
        void generate_indices_for_states();
        void generate_reduce_transitions();
        void generate_reduce_transition( ParserState* state, const ParserSymbol* symbol, const ParserProduction* production );
        void generate_indices_for_transitions();
};

}

}

#endif
