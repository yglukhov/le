//
// LexerItem.hpp
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

#ifndef SWEET_LEXER_LEXERITEM_HPP_INCLUDED
#define SWEET_LEXER_LEXERITEM_HPP_INCLUDED

#include "declspec.hpp"
#include "RegexNodeLess.hpp"
#include <sweet/pointer/ptr.hpp>
#include <string>
#include <set>

namespace sweet
{

namespace lexer
{

class RegexNode;
class LexerAction;

/**
// An item that defines the positions in a regular expression that a state 
// represents.
*/
class SWEET_LEXER_DECLSPEC LexerItem
{
    std::set<RegexNode*, RegexNodeLess> next_nodes_; ///< The nodes that appear after the dot in this item.

    public:
        LexerItem();
        LexerItem( const std::set<RegexNode*, RegexNodeLess>& next_nodes );
        
        const std::set<RegexNode*, RegexNodeLess>& get_next_nodes() const;
        std::set<RegexNode*, RegexNodeLess> next_nodes( int begin, int end ) const;
        const LexerAction* find_action_by_interval( int begin, int end ) const;
        void describe( std::string* description ) const;
        bool operator<( const LexerItem& item ) const;
};

}

}

#endif
