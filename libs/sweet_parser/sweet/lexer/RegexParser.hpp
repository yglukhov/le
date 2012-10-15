//
// RegexParser.hpp
// Copyright (c) 2007 - 2011 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LEXER_REGEXPARSER_HPP_INCLUDED
#define SWEET_LEXER_REGEXPARSER_HPP_INCLUDED

#include "RegexCharacter.hpp"
#include "RegexNodeLess.hpp"
#include "RegexNodeType.hpp"
#include "LexerToken.hpp"
#include <sweet/pointer/ptr.hpp>
#include <string>
#include <vector>
#include <set>

namespace sweet
{

namespace lexer
{

class LexerGenerator;
class LexerAction;
class RegexNode;

/**
// @internal
//
// Parse regular expressions.
*/
class RegexParser
{
    LexerGenerator* lexer_generator_; ///< The LexerGenerator to retrieve actions from and report errors and debug information to.
    std::set<RegexCharacter> bracket_expression_characters_; ///< The characters in the current bracket expression.
    int index_; ///< The current node index.
    std::vector<ptr<RegexNode> > nodes_; ///< The current nodes.
    int errors_; ///< The number of errors that have occured.

    public:
        RegexParser( const LexerToken& token, LexerGenerator* lexer_generator );
        RegexParser( const std::vector<LexerToken>& tokens, LexerGenerator* lexer_generator );

        bool empty() const;
        int errors() const;
        const ptr<RegexNode>& node() const;
        void print() const;

        void cat_expression();
        void or_expression();
        void star_expression();
        void plus_expression();
        void optional_expression();
        void begin_bracket_expression();
        void begin_negative_bracket_expression();
        void end_bracket_expression();
        void action_expression( const std::string& identifier );
        void character( int character );
        void dot();
        void item_range( int begin, int end );
        void item_character( int character );
        void item_alnum();
        void item_word();
        void item_alpha();
        void item_blank();
        void item_cntrl();
        void item_digit();
        void item_graph();
        void item_lower();
        void item_print();
        void item_punct();
        void item_space();
        void item_upper();
        void item_xdigit();
        void negative_item_range( int begin, int end );
        void negative_item_character( int character );
        void negative_item_alnum();
        void negative_item_word();
        void negative_item_alpha();
        void negative_item_blank();
        void negative_item_cntrl();
        void negative_item_digit();
        void negative_item_graph();
        void negative_item_lower();
        void negative_item_print();
        void negative_item_punct();
        void negative_item_space();
        void negative_item_upper();
        void negative_item_xdigit();

    private:
        ptr<RegexNode> regex_node( RegexNodeType type );
        ptr<RegexNode> regex_node( int begin, int end );
        ptr<RegexNode> regex_node( int begin, int end, const LexerToken* token );
        ptr<RegexNode> regex_node( const LexerAction* action );

        void print_positions( const std::set<RegexNode*, RegexNodeLess>& positions ) const;
        void print_nodes( const std::vector<ptr<RegexNode> >& nodes, int level ) const;

        void calculate_symbols_for_characters_start_and_end();
        void calculate_combined_parse_tree( const std::vector<LexerToken>& tokens );
        void calculate_nullable_first_last_and_follow();
        void parse_regular_expression( const LexerToken& token );
        void parse_literal( const LexerToken& token );

        int escape( std::string::const_iterator start, std::string::const_iterator end, std::string::const_iterator* next ) const;
        void insert_characters( int begin, int end );
        void erase_characters( int begin, int end );
        void insert_characters( const char* characters );
        void erase_characters( const char* characters );
};

}

}

#endif
