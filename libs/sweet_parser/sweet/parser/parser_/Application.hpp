//
// Application.hpp
// Copyright (c) 2007 - 2010 Charles Baker.  All rights reserved.
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

#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <sweet/pointer/ptr.hpp>
#include <sweet/lua/Lua.hpp>
#include <sweet/lua/LuaObject.hpp>

namespace sweet
{


namespace lexer
{

class LexerStateMachine;
class LexerState;
class LexerTransition;
class LexerAction;

}

namespace parser
{

class ParserSymbol;
class ParserStateMachine;
class ParserState;
class ParserTransition;
class ParserSymbol;
class ParserAction;
class ParserProduction;

class Application
{
    int result_;
    lua::Lua lua_;
    lua::LuaObject parser_state_machine_prototype_;
    lua::LuaObject parser_state_machine_metatable_;
    lua::LuaObject parser_state_prototype_;
    lua::LuaObject parser_state_metatable_;
    lua::LuaObject parser_transition_prototype_;
    lua::LuaObject parser_transition_metatable_;
    lua::LuaObject parser_symbol_prototype_;
    lua::LuaObject parser_symbol_metatable_;
    lua::LuaObject parser_action_prototype_;
    lua::LuaObject parser_action_metatable_;
    lua::LuaObject parser_production_prototype_;
    lua::LuaObject parser_production_metatable_;
    lua::LuaObject lexer_state_machine_prototype_;
    lua::LuaObject lexer_state_machine_metatable_;
    lua::LuaObject lexer_state_prototype_;
    lua::LuaObject lexer_state_metatable_;
    lua::LuaObject lexer_transition_prototype_;
    lua::LuaObject lexer_transition_metatable_;    
    lua::LuaObject lexer_action_prototype_;
    lua::LuaObject lexer_action_metatable_;

    public:
        Application( int argc, char** argv );
        int get_result() const;
        
    private:
        friend class ParserStateMachineDeleter;
        ptr<ParserStateMachine> parser_state_machine( const std::string& grammar, const std::string& filename );
        void prototypes();
        void add_parser_state_machine( ptr<ParserStateMachine> parser_state_machine );
        void remove_parser_state_machine( ParserStateMachine* parser_state_machine );
        void add_parser_state( ParserState* state );
        void remove_parser_state( ParserState* state );
        void add_parser_transition( ParserTransition* transition );
        void remove_parser_transition( ParserTransition* transition );
        void add_parser_symbol( ParserSymbol* symbol );
        void remove_parser_symbol( ParserSymbol* symbol );        
        void add_parser_action( ParserAction* action );
        void remove_parser_action( ParserAction* action );
        void add_parser_production( ParserProduction* production );
        void remove_parser_production( ParserProduction* production );
        void add_lexer_state_machine( const lexer::LexerStateMachine* data );
        void remove_lexer_state_machine( const lexer::LexerStateMachine* data );
        void add_lexer_state( lexer::LexerState* state );
        void remove_lexer_state( lexer::LexerState* state );
        void add_lexer_transition( lexer::LexerTransition* transition );
        void remove_lexer_transition( lexer::LexerTransition* transition );
        void add_lexer_action( lexer::LexerAction* action );
        void remove_lexer_action( lexer::LexerAction* action );
        ParserSymbol* symbol( lexer::LexerState* state ) const;
};

}

}

#endif
