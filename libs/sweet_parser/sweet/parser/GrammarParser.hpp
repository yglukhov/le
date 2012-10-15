//
// GrammarParser.hpp
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

#ifndef GRAMMARPARSER_INCLUDED
#define GRAMMARPARSER_INCLUDED

#include <sweet/parser/ParserSymbol.hpp>
#include <sweet/parser/ParserGrammar.hpp>
#include <sweet/lexer/LexerToken.hpp>
#include <map>
#include <string>

namespace sweet
{

namespace parser
{

class ParserErrorPolicy;

/**
// @internal
//
// Parse grammars.
*/
class GrammarParser
{
    ParserErrorPolicy* error_policy_;
    std::string identifier_;
    std::string lexeme_;
    SymbolAssociativity associativity_;
    ParserSymbol* symbol_;
    int precedence_;
    std::map<std::pair<lexer::LexerTokenType, std::string>, ParserSymbol*> symbols_;
    std::map<std::string, ParserAction*> actions_;
    ParserGrammar grammar_;
    std::vector<lexer::LexerToken> tokens_;
    std::vector<lexer::LexerToken> whitespace_tokens_;
    int errors_;

    public:
        GrammarParser( const char* filename, ParserErrorPolicy* error_policy );
        GrammarParser( const char* start, const char* finish, ParserErrorPolicy* error_policy );

        ParserGrammar& grammar();        
        std::vector<lexer::LexerToken>& tokens();
        std::vector<lexer::LexerToken>& whitespace_tokens();
        int errors() const;

        ParserSymbol* symbol( SymbolType type, lexer::LexerTokenType token_type, const std::string& lexeme, int line );
        ParserAction* action( const std::string& identifier );
        
        void begin_grammar();
        void associativity( SymbolAssociativity associativity );
        void associate( lexer::LexerTokenType type );
        void precedence( lexer::LexerTokenType type );
        void whitespace_directive( lexer::LexerTokenType type );    
        void begin_production( const std::string& identifier, int line );
        void end_and_begin_production( int line );
        void end_production();
        void cat_expression();
        void action_identifier();
        void literal_terminal();
        void regex_terminal();
        void identifier();
        void lexeme( const std::string& lexeme );
        void syntax_error( int line );
        void syntax_error_in_grammar( int line );
};

}

}

#endif
