//
// ParserSymbol.hpp
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

#ifndef SWEET_PARSER_SYMBOL_HPP_INCLUDED
#define SWEET_PARSER_SYMBOL_HPP_INCLUDED

#include "declspec.hpp"
#include <sweet/pointer/ptr.hpp>
#include <sweet/pointer/enable_ptr_from_this.hpp>
#include <set>
#include <vector>
#include <string>

namespace sweet
{

namespace parser
{

/**
// The type of a symbol.
//
// @relates ParserSymbol
*/
enum SymbolType
{
    SYMBOL_NULL, ///< Null type.
    SYMBOL_TERMINAL, ///< Terminal symbols.
    SYMBOL_NON_TERMINAL, ///< Non-terminal symbols.
    SYMBOL_END ///< The end symbol.
};

/**
// The associativity of a symbol.
//
// @relates ParserSymbol
*/
enum SymbolAssociativity
{
    ASSOCIATE_NULL, ///< The symbol has undefined associativity.
    ASSOCIATE_NONE, ///< The symbol has no associativity.
    ASSOCIATE_LEFT, ///< The symbol associates to the left.
    ASSOCIATE_RIGHT ///< The symbol associates to the right.
};

class ParserProduction;

/**
// A symbol parsed as part of a grammar rule.
*/
class SWEET_PARSER_DECLSPEC ParserSymbol : public pointer::enable_ptr_from_this<ParserSymbol>
{
    public:
        static const int INVALID_INDEX = -1;
        
    private:
        SymbolType type_; ///< The type of this symbol.
        std::string lexeme_; ///< The lexeme for this symbol.
        std::string identifier_; ///< The identifier for this symbol (generated from its lexeme).
        int line_; ///< The line that this symbol was defined on.
        std::vector<ptr<ParserProduction> > productions_; ///< The productions for this symbol.
        int precedence_; ///< The precedence of this symbol (0 indicates no precedence).
        SymbolAssociativity associativity_; ///< The associativity of this symbol.
        bool nullable_; ///< True if this symbol is nullable otherwise false.
        std::set<const ParserSymbol*> first_; ///< The symbols that can start this symbol in a production or regular expression.
        std::set<const ParserSymbol*> follow_; ///< The symbols that can follow this symbol in a production or regular expression.
        int index_; ///< The index of this symbol.

    public:
        ParserSymbol();
        ParserSymbol( SymbolType type, const std::string& lexeme, int line );

        const std::string& get_lexeme() const;
        const std::string& get_identifier() const;

        void set_type( SymbolType type );
        SymbolType get_type() const;

        void set_line( int line );
        int get_line() const;

        void append_production( ptr<ParserProduction> production );
        const std::vector<ptr<ParserProduction> >& get_productions() const;

        bool is_nullable() const;
        void replace_by_non_terminal( const ParserSymbol* non_terminal_symbol );
        ParserSymbol* get_implicit_terminal() const;

        int add_symbol_to_first( const ParserSymbol* symbol );
        int add_symbols_to_first( const std::set<const ParserSymbol*>& symbols );
        const std::set<const ParserSymbol*>& get_first() const;

        int add_symbol_to_follow( const ParserSymbol* symbol );
        int add_symbols_to_follow( const std::set<const ParserSymbol*>& symbols );
        const std::set<const ParserSymbol*>& get_follow() const;
        
        void set_precedence( int precedence );
        int get_precedence() const;
        
        void set_associativity( SymbolAssociativity associativity );
        SymbolAssociativity get_associativity() const;
        
        void calculate_identifier();
        int calculate_first();
        int calculate_follow();

        void set_index( int index );
        int get_index() const;

        void describe( std::string* description ) const;
        static void describe( const std::set<const ParserSymbol*>& symbols, std::string* description );
        std::string description() const;

    private:
        const char* name( int character ) const;
};

}

}

#endif
