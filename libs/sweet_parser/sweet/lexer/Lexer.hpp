//
// Lexer.hpp
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

#ifndef SWEET_LEXER_LEXER_HPP_INCLUDED
#define SWEET_LEXER_LEXER_HPP_INCLUDED

#if defined(BUILD_PLATFORM_MSVC) || 1
#include <functional>
#else
#include <tr1/functional>
#endif

namespace sweet
{

namespace lexer
{

class LexerAction;
class LexerState;
class LexerStateMachine;
class LexerErrorPolicy;

/**
// A lexical analyzer.
*/
template <class Iterator, class Char = typename std::iterator_traits<Iterator>::value_type, class Traits = typename std::char_traits<Char>, class Allocator = typename std::allocator<Char> >
class Lexer
{
    typedef std::tr1::function<void (Iterator* begin, Iterator end, std::basic_string<Char, Traits, Allocator>* lexeme, const void** symbol)> LexerActionFunction;

    struct LexerActionHandler
    {
        const LexerAction*  action_;
        LexerActionFunction function_;
        LexerActionHandler( const LexerAction* action, LexerActionFunction function );
    };

    const LexerStateMachine*                   state_machine_;   ///< The state machine for this lexer.
    const void*                                end_symbol_;      ///< The value to return to indicate that the end of the input has been reached.
    LexerErrorPolicy*                          error_policy_;    ///< The error policy this lexer uses to report errors and debug information.
    std::vector<LexerActionHandler>            action_handlers_; ///< The action handlers for this Lexer.
    Iterator                                   position_;        ///< The current position of this Lexer in its input sequence.
    Iterator                                   end_;             ///< One past the last position of the input sequence for this Lexer.
    std::basic_string<Char, Traits, Allocator> lexeme_;          ///< The most recently matched lexeme.
    const void*                                symbol_;          ///< The most recently matched symbol or null if no symbol has been matched.
    bool                                       full_;            ///< True when this Lexer scanned all of its input otherwise false.

    public:
        Lexer( const LexerStateMachine* state_machine, const void* end_symbol, LexerErrorPolicy* error_policy = NULL );
        void set_action_handler( const char* identifier, LexerActionFunction function );
        const std::basic_string<Char, Traits, Allocator>& lexeme() const;
        const void* symbol() const;
        const Iterator& position() const;
        bool full() const;
        void reset( Iterator start, Iterator finish );
        void advance();
        
    private:
        void skip();
        const void* run();
        void error();
};

}

}

#endif
