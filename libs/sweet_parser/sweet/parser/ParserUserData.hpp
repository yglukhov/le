//
// ParserUserData.hpp
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

#ifndef SWEET_PARSER_PARSERUSERDATA_HPP_INCLUDED
#define SWEET_PARSER_PARSERUSERDATA_HPP_INCLUDED

#include <sweet/pointer/ptr.hpp>
#include <string>
#include <vector>

namespace sweet
{

namespace parser
{

class ParserSymbol;
template <class UserData, class Char, class Traits, class Allocator> class ParserNode;

/**
// The default implementation for data stored in a parser's stack.
*/
template <class Char, class Traits = typename std::char_traits<Char>, class Allocator = typename std::allocator<Char> >
class ParserUserData
{
    typedef ParserNode<ptr<ParserUserData>, Char, Traits, Allocator> ParserNode;

    const ParserSymbol* symbol_; ///< The symbol at this user data's node.
    std::basic_string<Char, Traits, Allocator> lexeme_; ///< The lexeme at this user data's node.
    std::vector<ptr<ParserUserData<Char, Traits, Allocator> > > user_datas_; ///< Children in the parse tree.
        
    public:
        ParserUserData( const ParserSymbol* symbol, const std::basic_string<Char, Traits, Allocator>& lexeme );  
        ParserUserData( const ParserSymbol* symbol, size_t user_datas );
        ParserUserData( const ParserSymbol* symbol, const ParserNode* start, const ParserNode* finish );

        const ParserSymbol* get_symbol() const;
        const std::basic_string<Char, Traits, Allocator>& get_lexeme() const;        
        void append_user_data( ptr<ParserUserData> user_data );
        const std::vector<ptr<ParserUserData<Char, Traits, Allocator> > >& get_user_datas() const;
};

}

}

#endif
