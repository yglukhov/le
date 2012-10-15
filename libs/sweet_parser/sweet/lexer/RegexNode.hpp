//
// RegexNode.hpp
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

#ifndef SWEET_LEXER_REGEXNODE_HPP_INCLUDED
#define SWEET_LEXER_REGEXNODE_HPP_INCLUDED

#include "RegexNodeLess.hpp"
#include "RegexNodeType.hpp"
#include <sweet/pointer/ptr.hpp>
#include <sweet/pointer/enable_ptr_from_this.hpp>
#include <set>
#include <vector>

namespace sweet
{

namespace lexer
{

/**
// @internal
//
// The character that marks the beginning of the valid character range.
//
// @relates RegexNode
*/
extern const int BEGIN_CHARACTER;

/**
// @internal
//
// The character that marks the end of hte valid character range.
//
// @relates RegexNode
*/
extern const int END_CHARACTER;

/**
// @internal
//
// The character that marks the beginning of the invalid character range.
//
// @relates RegexNode
*/
extern const int INVALID_BEGIN_CHARACTER;

/**
// @internal
//
// The character that marks the end of the invalid character range.
//
// @relates RegexNode
*/
extern const int INVALID_END_CHARACTER;

class LexerToken;
class LexerAction;

/**
// @internal
//
// A node in a parsed regular expression.
*/
class RegexNode : public pointer::enable_ptr_from_this<RegexNode>
{
    int index_; ///< The index of the node.
    RegexNodeType type_; ///< The type of the node.
    int begin_character_; ///< The first character in the interval of characters represented by the node.
    int end_character_; ///< One past the last character in the interval of characters represented by the node.
    const LexerToken* token_; ///< The token recognized at the node or null if the node doesn't recognize a token.
    const LexerAction* action_; ///< The action taken at the node or null if no action is taken at the node.
    std::vector<ptr<RegexNode> > nodes_; ///< The child nodes.
    bool nullable_; ///< True if the node is nullable otherwise false.
    std::set<RegexNode*, RegexNodeLess> first_positions_; ///< The first positions at the node.
    std::set<RegexNode*, RegexNodeLess> last_positions_; ///< The last positions at the node.
    std::set<RegexNode*, RegexNodeLess> follow_positions_; ///< The follow positions at the node.

    public:
        RegexNode( int index, RegexNodeType type );
        RegexNode( int index, int begin_character, int end_character );
        RegexNode( int index, int begin_character, int end_character, const LexerToken* token );
        RegexNode( int index, const LexerAction* action );

        int get_index() const;
        RegexNodeType get_type() const;
        const char* get_lexeme() const;
        int get_begin_character() const;
        int get_end_character() const;
        const LexerToken* get_token() const;
        const LexerAction* get_action() const;
        bool is_match( int begin, int end ) const;
        bool is_end() const;
        bool is_action() const;

        void add_node( const ptr<RegexNode>& node );
        RegexNode* get_node( int index ) const;
        const std::vector<ptr<RegexNode> >& get_nodes() const;

        bool is_nullable() const;
        const std::set<RegexNode*, RegexNodeLess>& get_first_positions() const;
        const std::set<RegexNode*, RegexNodeLess>& get_last_positions() const;
        const std::set<RegexNode*, RegexNodeLess>& get_follow_positions() const;
        const std::set<RegexNode*, RegexNodeLess>& get_next_positions() const;

        void calculate_nullable();
        void calculate_first_positions();
        void calculate_last_positions();
        void calculate_follow_positions();

        bool operator<( const RegexNode& node ) const;

        void print( const std::set<RegexNode*>& dot_nodes ) const;
};

}

}

#endif
