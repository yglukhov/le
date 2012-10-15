//
// Parser.hpp
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

#ifndef SWEET_PARSER_PARSER_HPP_INCLUDED
#define SWEET_PARSER_PARSER_HPP_INCLUDED

#include "ParserNode.hpp"
#include "ParserUserData.hpp"
#include "AddParserActionHandler.hpp"
#include <sweet/pointer/ptr.hpp>
#include <sweet/lexer/Lexer.hpp>
#include <sweet/lexer/AddLexerActionHandler.hpp>
#include <functional>
#include <vector>

namespace sweet
{

namespace error
{

class Error;

}

namespace parser
{

class ParserErrorPolicy;
class ParserAction;
class ParserSymbol;
class ParserProduction;
class ParserTransition;
class ParserState;
class ParserStateMachine;
class ParserErrorPolicy;

/**
// A %parser.
*/
template <class Iterator, class UserData = ptr<ParserUserData<typename std::iterator_traits<Iterator>::value_type> >, class Char = typename std::iterator_traits<Iterator>::value_type, class Traits = typename std::char_traits<Char>, class Allocator = typename std::allocator<Char> >
class Parser
{
    public:
        typedef ParserNode<UserData, Char, Traits, Allocator> ParserNode;
        typedef typename std::vector<ParserNode>::const_iterator ParserNodeConstIterator;
        typedef std::tr1::function<void ( Iterator* begin, Iterator end, std::basic_string<Char, Traits, Allocator>* lexeme, const ParserSymbol** symbol)> LexerActionFunction;
        typedef std::tr1::function<UserData (const ParserSymbol* symbol, const ParserNode* start, const ParserNode* finish)> ParserActionFunction;

	::sokira::le::CLexer::Ptr mLexer;

    private:
        struct ParserActionHandler
        {        
            const ParserAction*  action_;
            ParserActionFunction function_;
            ParserActionHandler( const ParserAction* action, ParserActionFunction function );
        };

        const ParserStateMachine* state_machine_; ///< The data that defines the state machine used by this parser.
        ParserErrorPolicy* error_policy_; ///< The error policy this parser uses to report errors and debug information.
        std::vector<ParserNode> nodes_; ///< The stack of nodes that store symbols that are shifted and reduced during parsing.
        //lexer::Lexer<Iterator, Char, Traits, Allocator> lexer_; ///< The lexical analyzer used during parsing.
        std::vector<ParserActionHandler> action_handlers_; ///< The action handlers for parser actions taken during reduction.
        ParserActionFunction default_action_handler_; ///< The default action handler for reductions that don't specify any action.
        bool debug_enabled_; ///< True if shift and reduce operations should be printed otherwise false.
        bool accepted_; ///< True if the parser accepted its input otherwise false.
        bool full_; ///< True if the parser processed all of its input otherwise false.

		const ParserSymbol* symbolFromToken(const ::sokira::le::CToken& token) const;
	
    public:
        Parser( const ParserStateMachine* state_machine, ParserErrorPolicy* error_policy = NULL, lexer::LexerErrorPolicy* lexer_error_policy = NULL );

		
	
        void reset();
        void parse( Iterator start, Iterator finish );
        bool parse( const void* symbol, const std::basic_string<Char, Traits, Allocator>& lexeme );
        bool parse( const ParserSymbol* symbol, const std::basic_string<Char, Traits, Allocator>& lexeme );
        bool accepted() const;
        bool full() const;
        const UserData& user_data() const;
        const Iterator& position() const;

        AddParserActionHandler<Iterator, UserData, Char, Traits, Allocator> parser_action_handlers();
        lexer::AddLexerActionHandler<Iterator, Char, Traits, Allocator> lexer_action_handlers();
        void set_default_action_handler( ParserActionFunction function );
        void set_action_handler( const char* identifier, ParserActionFunction function );

        void fire_error( const error::Error& error ) const;
        void fire_printf( const char* format, ... ) const;
        
        void set_debug_enabled( bool debug_shift_enabled );
        bool is_debug_enabled() const;
        
    private:
        const ParserTransition* find_transition( const ParserSymbol* symbol, const ParserState* state ) const;
        typename std::vector<ParserNode>::iterator find_node_to_reduce_to( const ParserProduction* production, std::vector<ParserNode>& nodes );
        void debug_shift( const ParserNode& node ) const;
        void debug_reduce( const ParserProduction* reduced_production, const ParserNode* start, const ParserNode* finish ) const;
        UserData handle( const ParserProduction* reduced_production, const ParserNode* start, const ParserNode* finish ) const;
        void shift( const ParserTransition* transition, const std::basic_string<Char, Traits, Allocator>& lexeme );
        void reduce( const ParserTransition* transition, bool* accepted, bool* rejected );
        void error( bool* accepted, bool* rejected );
};

}

}

#endif
