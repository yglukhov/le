//
// ParserItem.hpp
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

#ifndef SWEET_PARSER_PARSERITEM_HPP_INCLUDED
#define SWEET_PARSER_PARSERITEM_HPP_INCLUDED

#include "declspec.hpp"
#include <sweet/pointer/ptr.hpp>
#include <string>
#include <set>

namespace sweet
{

namespace parser
{

class ParserSymbol;
class ParserProduction;

/**
// An item that defines the positions in the grammar that a state 
// represents.
*/
class SWEET_PARSER_DECLSPEC ParserItem
{
    ptr<ParserProduction> production_; ///< The production that this item is for.
    int position_; ///< The position of the dot in this item.
    mutable std::set<const ParserSymbol*> lookahead_symbols_; ///< The lookahead Symbols for this item.

    public:
        ParserItem();
        ParserItem( ptr<ParserProduction> production, int position );

        ptr<ParserProduction> get_production() const;
        int get_position() const;
        bool is_dot_at_beginning() const;
        bool is_dot_at_end() const;
        bool is_next_node( const ParserSymbol& symbol ) const;
        void describe( std::string* description ) const;

        int add_lookahead_symbols( const std::set<const ParserSymbol*>& lookahead_symbols ) const;
        const std::set<const ParserSymbol*>& get_lookahead_symbols() const;

        bool operator<( const ParserItem& item ) const;
};

}

}

#endif
