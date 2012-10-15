// 
// ParserGrammar.cpp
// Copyright (c) 2010 - 2011 Charles Baker.  All rights reserved.
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
#include "ParserGrammar.hpp"
#include "parser_types.hpp"
#include "ParserGenerator.hpp"
#include "ParserProduction.hpp"
#include "ParserAction.hpp"
#include "Error.hpp"
#include <sweet/pointer/ptr.hpp>
#include <stdio.h>

using std::set;
using std::vector;
using namespace sweet;
using namespace sweet::lexer;
using namespace sweet::parser;

/**
// Constructor.
//
// @param actions_reserve
//  The number of actions to reserve space for in this ParserGrammar.
//
// @param productions_reserve
//  The number of productions to reserve space for in this ParserGrammar.
//
// @param symbols_reserve
//  The number of symbols to reserve space for in this ParserGrammar.
*/
ParserGrammar::ParserGrammar( size_t actions_reserve, size_t productions_reserve, size_t symbols_reserve )
: identifier_(),
  actions_(),
  productions_(),
  symbols_(),
  start_symbol_( NULL ),
  end_symbol_( NULL ),
  error_symbol_( NULL ),
  index_( 0 )
{
    actions_.reserve( actions_reserve );
    productions_.reserve( productions_reserve );
    symbols_.reserve( symbols_reserve );
    start_symbol_ = add_non_terminal( ".start", 0 );
    end_symbol_ = add_symbol( SYMBOL_END, ".end", 0 );
    error_symbol_ = add_terminal( ".error", 0 );
}

/**
// Get the identifier of this ParserGrammar.
//
// @return
//  The identifier.
*/
std::string& ParserGrammar::identifier()
{
    return identifier_;
}

/**
// Get the actions in this ParserGrammar.
//
// @return
//  The actions.
*/
std::vector<ptr<ParserAction> >& ParserGrammar::actions()
{
    return actions_;
}

/**
// Get the productions in this ParserGrammar.
//
// @return
//  The productions.
*/
std::vector<ptr<ParserProduction> >& ParserGrammar::productions()
{
    return productions_;
}

/**
// Get the symbols in this ParserGrammar.
//
// @return
//  The symbols.
*/
std::vector<ptr<ParserSymbol> >& ParserGrammar::symbols()
{
    return symbols_;
}

/**
// Get the start symbol in this ParserGrammar.
//
// @return
//  The start symbol.
*/
ParserSymbol* ParserGrammar::start_symbol() const
{
    return start_symbol_;
}

/**
// Get the end symbol in this ParserGrammar.
//
// @return
//  The end symbol.
*/
ParserSymbol* ParserGrammar::end_symbol() const
{
    return end_symbol_;
}

/**
// Get the error symbol in this ParserGrammar.
//
// @return
//  The error symbol.
*/
ParserSymbol* ParserGrammar::error_symbol() const
{
    return error_symbol_;
}

/**
// Add a symbol to this ParserGrammar.
//
// @param type
//  The type of symbol to add.
//
// @param identifier
//  The identifier to use for the symbol (for debugging purposes only).
//
// @param line
//  The line that the symbol first appears on (for debugging purposes only).
//
// @return
//  The symbol.
*/
ParserSymbol* ParserGrammar::add_symbol( SymbolType type, const std::string& identifier, int line )
{
    ptr<ParserSymbol> symbol( new ParserSymbol(type, identifier, line) );
    symbols_.push_back( symbol );
    return symbol.get();
}

/**
// Add a terminal symbol to this ParserGrammar.
//
// @param identifier
//  The identifier to use for the symbol (for debugging purposes only).
//
// @param line
//  The line that the symbol first appears on (for debugging purposes only).
//
// @return
//  The terminal symbol.
*/
ParserSymbol* ParserGrammar::add_terminal( const std::string& identifier, int line )
{
    return add_symbol( SYMBOL_TERMINAL, identifier, line );
}

/**
// Add a non terminal symbol to this ParserGrammar.
//
// @param identifier
//  The identifier to use for the symbol (for debugging purposes only).
//
// @param line
//  The line that the symbol first appears on (for debugging purposes only).
//
// @return
//  The terminal symbol.
*/
ParserSymbol* ParserGrammar::add_non_terminal( const std::string& identifier, int line )
{
    return add_symbol( SYMBOL_NON_TERMINAL, identifier, line );
}

/**
// Add an action to this ParserGrammar.
//
// @param identifier
//  The identifier of the action to add.
//
// @return
//  The action.
*/
ParserAction* ParserGrammar::add_action( const std::string& identifier )
{
    SWEET_ASSERT( !identifier.empty() );    
    ptr<ParserAction> action;

    if ( !identifier.empty() )
    {
        std::vector<ptr<ParserAction> >::const_iterator i = actions_.begin();
        while ( i != actions_.end() && (*i)->get_identifier() != identifier )
        {
            ++i;
        }
        
        if ( i != actions_.end() )
        {
            action = *i;
        }
        else
        {
            action.reset( new ParserAction(int(actions_.size()), identifier) );
            actions_.push_back( action );
        }
    }
    
    return action.get();
}

/**
// Set the identifier for this ParserGrammar (optional).
//
// @param identifier
//  The identifier for this ParserGrammar.
*/
void ParserGrammar::identifier( const std::string& identifier )
{
    identifier_ = identifier;
}

/**
// Start a production in this ParserGrammar.
//
// @param symbol
//  The symbol on the left hand side of the production (assumed not null).
//
// @param line
//  The line that the production starts on.
*/
void ParserGrammar::begin_production( ParserSymbol* symbol, int line )
{
    if ( productions_.empty() )
    {
        SWEET_ASSERT( start_symbol_ );
        SWEET_ASSERT( end_symbol_ );

        ptr<ParserProduction> production( new ParserProduction(int(productions_.size()), start_symbol_, 0, NULL) );
        productions_.push_back( production );
        ParserGrammar::symbol( symbol );
        start_symbol_->append_production( production );        
    }

    SWEET_ASSERT( symbol );
    ptr<ParserProduction> production( new ParserProduction(int(productions_.size()), symbol, line, NULL) );
    productions_.push_back( production );
    symbol->append_production( production );
}

/**
// End a production.
//
// If there is more than one node then this end production has been matched as
// part of a top level '|' expression and the right hand node is really the 
// first symbol in another production for the same symbol as the current 
// production.  It will be reduced later when another top level '|' expression
// or the ';' at the end of the production is matched.
*/
void ParserGrammar::end_production()
{
}

/**
// Append a symbol node to the current production's right hand side.
//
// @param symbol
//  The symbol to append on the right hand side (assumed not null).
*/
void ParserGrammar::symbol( ParserSymbol* symbol )
{
    SWEET_ASSERT( symbol );
    SWEET_ASSERT( !productions_.empty() );
    ParserProduction* production = productions_.back().get();
    production->append_symbol( symbol );
}

/**
// Set the action to be taken when the current production is reduced.
//
// @param action
//  The action to take when the current production is reduced.
*/
void ParserGrammar::action( ParserAction* action )
{
    SWEET_ASSERT( !productions_.empty() );
    productions_.back()->set_action( action );
}

/**
// Set the precedence of the current production to match the precedence
// give to \e symbol.
//
// @param symbol
//  The symbol to set the precedence of the current production to match 
//  (assumed not null).
*/
void ParserGrammar::precedence_symbol( ParserSymbol* symbol )
{
    SWEET_ASSERT( !productions_.empty() );
    productions_.back()->set_precedence_symbol( symbol );
}

/**
// Print this grammar to stdout.
*/
void ParserGrammar::print() const
{
    for ( vector<ptr<ParserSymbol> >::const_iterator i = symbols_.begin(); i != symbols_.end(); ++i )
    {
        const ParserSymbol* symbol = i->get();
        SWEET_ASSERT( symbol );
        if ( symbol->get_type() == SYMBOL_NON_TERMINAL )
        {
            printf( "%s:\n", symbol->description().c_str() );        
            printf( "  nullable=%s\n", symbol->is_nullable() ? "true" : "false" );
            std::string description;
            description.reserve( 1024 );
            ParserSymbol::describe( symbol->get_first(), &description );
            printf( "  first=(%s)\n", description.c_str() );
            description.clear();
            ParserSymbol::describe( symbol->get_follow(), &description );
            printf( "  follow=(%s)\n", description.c_str() );
            printf( "\n\n" );
        }
    }

    for ( vector<ptr<ParserProduction> >::const_iterator i = productions_.begin(); i != productions_.end(); ++i )
    {
        const ParserProduction* production = i->get();
        SWEET_ASSERT( production );
        printf( "%s:\n", production->description().c_str() );
        printf( "\n\n" );
    }
}

/**
// Print the nodes in \e positions.
//
// @param positions
//  The nodes that appear after the dot in a production.
*/
void ParserGrammar::print_positions( const std::set<int>& positions ) const
{
    set<int>::const_iterator i = positions.begin();
    if ( i != positions.end() )
    {
        printf( "%d", *i );
        ++i;
    }
    while ( i != positions.end() )
    {
        printf( ", %d", *i );
        ++i;
    }
}

/**
// Calculate identifiers for all symbols.
*/
void ParserGrammar::calculate_identifiers()
{
    for ( vector<ptr<ParserSymbol> >::const_iterator i = symbols_.begin(); i != symbols_.end(); ++i )
    {
        ParserSymbol* symbol = i->get();
        SWEET_ASSERT( symbol );
        symbol->calculate_identifier();
    }
}

/**
// Replace references to \e to_symbol with references to \e with_symbol.
//
// @param to_symbol
//  The ParserSymbol to replace references to.
//
// @param with_symbol
//  The ParserSymbol to replace references with.
*/
void ParserGrammar::replace_references_to_symbol( ParserSymbol* to_symbol, ParserSymbol* with_symbol )
{
    for ( std::vector<ptr<ParserProduction> >::const_iterator i = productions_.begin(); i != productions_.end(); ++i )
    {
        ParserProduction* production = i->get();
        SWEET_ASSERT( production );
        production->replace_references_to_symbol( to_symbol, with_symbol );
    }
}

/**
// Calculate the non terminal symbols that are really just named terminals.
//
// Any symbols that contain a single production that contains only a terminal 
// symbol are really just acting as names for that terminal symbol.  To make 
// the parser easier to understand and more efficient these symbols are 
// collapsed by making any references to the non terminal symbol refer directly
// to the terminal symbol.  The identifier of the terminal is changed to be 
// the more readable name of the non terminal.
//
// For example the rule 'integer: "[0-9]+";' creates a non terminal
// symbol 'integer' and a terminal symbol '"[0-9]+"'.  The non terminal
// symbol 'integer' is redundant from the point of view of the parser as it
// adds only a trivial reduction from one symbol type to another.  To optimize
// this situation the terminal is collapsed into the non terminal keeping the
// more readable name of the non terminal but removing the redundant 
// reduction.
*/
void ParserGrammar::calculate_implicit_terminal_symbols()
{
    for ( vector<ptr<ParserSymbol> >::iterator i = symbols_.begin(); i != symbols_.end(); ++i )
    {
        ParserSymbol* non_terminal_symbol = i->get();        
        if ( non_terminal_symbol && non_terminal_symbol != error_symbol_ )
        {
            ParserSymbol* terminal_symbol = non_terminal_symbol->get_implicit_terminal();
            if ( terminal_symbol )
            {       
                SWEET_ASSERT( terminal_symbol != non_terminal_symbol );
                terminal_symbol->replace_by_non_terminal( non_terminal_symbol );
                replace_references_to_symbol( non_terminal_symbol, terminal_symbol );
                i->reset();
            }
        }
    }
    
    vector<ptr<ParserSymbol> >::iterator i = symbols_.begin();
    while ( i != symbols_.end() )
    {
        if ( !i->get() )
        {
            i = symbols_.erase( i );
        }
        else        
        {
            ++i;
        }
    }
}

/**
// Calculate the first position sets for each ParserSymbol until no more 
// terminals can be added to any first position sets.
*/
void ParserGrammar::calculate_first()
{
    int added = 1;
    while ( added > 0 )
    {
        added = 0;
        for ( vector<ptr<ParserSymbol> >::iterator i = symbols_.begin(); i != symbols_.end(); ++i )
        {
            ParserSymbol* symbol = i->get();
            SWEET_ASSERT( symbol );
            added += symbol->calculate_first();
        }
    }
}

/**
// Calculate the follow position sets for each ParserSymbol until no more 
// terminals can be added to any follow position sets.
*/
void ParserGrammar::calculate_follow()
{
    start_symbol_->add_symbol_to_follow( end_symbol_ );

    int added = 1;
    while ( added > 0 )
    {
        added = 0;
        for ( vector<ptr<ParserSymbol> >::iterator i = symbols_.begin(); i != symbols_.end(); ++i )
        {
            ParserSymbol* symbol = i->get();
            SWEET_ASSERT( symbol );
            added += symbol->calculate_follow();
        }
    }
}

/**
// Calculate the index for each symbol.
*/
void ParserGrammar::calculate_indices()
{
    int index = 0;
    for ( vector<ptr<ParserSymbol> >::iterator i = symbols_.begin(); i != symbols_.end(); ++i )
    {
        ParserSymbol* symbol = i->get();
        SWEET_ASSERT( symbol );
        symbol->set_index( index );
        ++index;
    }
}

/**
// Calculate the precedence of each production that hasn't had precedence
// set explicitly as the precedence of its rightmost terminal.
*/
void ParserGrammar::calculate_precedence_of_productions()
{
    for ( vector<ptr<ParserProduction> >::const_iterator i = productions_.begin(); i != productions_.end(); ++i )
    {
        ParserProduction* production = i->get();
        SWEET_ASSERT( production );       
        if ( production->get_precedence() == 0 )
        {
            const ParserSymbol* symbol = production->find_rightmost_terminal_symbol();
            if ( symbol )
            {
                production->set_precedence_symbol( symbol );
            }
        }
    }
}

/**
// Check for symbols in the grammar that are referenced but never defined.
*/
void ParserGrammar::check_for_undefined_symbol_errors( ParserGenerator* generator )
{
    SWEET_ASSERT( generator );

    if ( generator->errors() == 0 )
    {
        for ( vector<ptr<ParserSymbol> >::const_iterator i = symbols_.begin(); i != symbols_.end(); ++i )
        {
            const ParserSymbol* symbol = i->get();
            SWEET_ASSERT( symbol );
            if ( symbol->get_type() == SYMBOL_NON_TERMINAL && symbol->get_productions().empty() )
            {
                generator->fire_error( 1, UndefinedSymbolError("Undefined symbol '%s' in grammar '%s'", symbol->get_identifier().c_str(), identifier_.c_str()) );
            }
        }
    }
}

/**
// Check for symbols in the grammar that are defined but never referenced.
//
// @param generator
//  The ParserGenerator for fire any errors from (assumed not null).
*/
void ParserGrammar::check_for_unreferenced_symbol_errors( ParserGenerator* generator )
{
    SWEET_ASSERT( generator );

    if ( generator->errors() == 0 )
    {
        for ( vector<ptr<ParserSymbol> >::const_iterator i = symbols_.begin(); i != symbols_.end(); ++i )
        {
            const ParserSymbol* symbol = i->get();
            SWEET_ASSERT( symbol );
            
            int references = 0;            
            if ( symbol != start_symbol_ && symbol != end_symbol_ && symbol != error_symbol_ )
            {
                for ( vector<ptr<ParserProduction> >::const_iterator i = productions_.begin(); i != productions_.end(); ++i )
                {
                    const ParserProduction* production = i->get();
                    SWEET_ASSERT( production );
                    if ( production->get_symbol()->get_type() != SYMBOL_TERMINAL )
                    {
                        references += production->count_references_to_symbol( symbol );
                    }
                }

                if ( references == 0 )
                {
                    generator->fire_error( 1, UnreferencedSymbolError("Unreferenced symbol '%s' in grammar '%s'", symbol->get_identifier().c_str(), identifier_.c_str()) );
                }
            }
        }
    }
}

/**
// Check for the error symbol being used in the left hand side of a 
// production.
//
// @param generator
//  The ParserGenerator for fire any errors from (assumed not null).
*/
void ParserGrammar::check_for_error_symbol_on_left_hand_side_errors( ParserGenerator* generator )
{
    SWEET_ASSERT( error_symbol_ );
    SWEET_ASSERT( generator );

    const vector<ptr<ParserProduction> >& productions = error_symbol_->get_productions();
    for ( vector<ptr<ParserProduction> >::const_iterator i = productions.begin(); i != productions.end(); ++i )
    {
        const ParserProduction* production = i->get();
        SWEET_ASSERT( production );
        generator->fire_error( 1, ErrorSymbolOnLeftHandSideError("The 'error' symbol appears on the left hand side of a production") );
    }
}
