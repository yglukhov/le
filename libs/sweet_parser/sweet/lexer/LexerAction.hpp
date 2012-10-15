//
// LexerAction.hpp
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

#ifndef SWEET_LEXER_LEXERACTION_HPP_INCLUDED
#define SWEET_LEXER_LEXERACTION_HPP_INCLUDED

#include "declspec.hpp"
#include <string>

namespace sweet
{

namespace lexer
{

/**
// An action that is attached to a lexical analyzer.
*/
class SWEET_LEXER_DECLSPEC LexerAction
{
    public:
        static const int INVALID_INDEX = -1;

    private:
        int         index_;      ///< The index of this action.
        std::string identifier_; ///< The identifier of this action.
    
    public:
        LexerAction( int index, const std::string& identifier );
        int get_index() const;
        const std::string& get_identifier() const;
};

}

}

#endif
