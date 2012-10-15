//
// ParserNode.hpp
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

#ifndef SWEET_PARSER_PARSERNODE_HPP_INCLUDED
#define SWEET_PARSER_PARSERNODE_HPP_INCLUDED

#include "ParserUserData.hpp"
#include <sweet/pointer/ptr.hpp>
#include <string>
#include <set>

namespace sweet
{

namespace parser
{

class ParserSymbol;
class ParserProduction;
class ParserState;

/**
// An element in the parser's stack when parsing.
*/
template <class UserData = ptr<ParserUserData<char> >, class Char = char, class Traits = std::char_traits<Char>, class Allocator = std::allocator<Char> >
class ParserNode
{
    const ParserState* state_; ///< The state at this node.
    const ParserSymbol* symbol_; ///< The symbol at this node.
    std::basic_string<Char, Traits, Allocator> lexeme_; ///< The lexeme at this node (empty if this node's symbol is a non-terminal).
    UserData user_data_; ///< The user data at this node.

    public:
        ParserNode( const ParserState* state, const ParserSymbol* symbol, const UserData& user_data );
        ParserNode( const ParserState* state, const ParserSymbol* symbol, const std::basic_string<Char, Traits, Allocator>& lexeme );
        
        const ParserState* get_state() const;        
        const ParserSymbol* get_symbol() const;
        const std::basic_string<Char, Traits, Allocator>& get_lexeme() const;
        const UserData& get_user_data() const;
};

}

}

#endif
