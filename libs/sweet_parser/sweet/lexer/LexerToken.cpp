//
// LexerToken.cpp
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
#include "LexerToken.hpp"

using namespace sweet::lexer;

LexerToken::LexerToken( LexerTokenType type, int line, const void* symbol, const std::string& lexeme )
: type_( type ),
  line_( line ),
  symbol_( symbol ),
  lexeme_( lexeme )
{
}

LexerTokenType LexerToken::type() const
{
    return type_;
}

int LexerToken::line() const
{
    return line_;
}

const void* LexerToken::symbol() const
{
    return symbol_;
}

const std::string& LexerToken::lexeme() const
{
    return lexeme_;
}
