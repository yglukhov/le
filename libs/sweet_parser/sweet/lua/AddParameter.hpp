//
// AddParameter.hpp
// Copyright (c) 2007  - 2010 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_ADDPARAMETER_HPP_INCLUDED
#define SWEET_LUA_ADDPARAMETER_HPP_INCLUDED

#include "declspec.hpp"
#include <string>

namespace sweet
{

namespace lua
{

class AddParameterHelper;
class LuaNil;
class LuaGlobalEnvironment;
class LuaValue;
class LuaObject;
class LuaThread;
class Lua;

/**
// A helper that provides a convenient syntax for calling functions.
*/
class SWEET_LUA_DECLSPEC AddParameter
{
    AddParameterHelper* add_parameter_helper_; ///< The AddParameterHelper that stores the state for this AddParameter.
   
    public:
        AddParameter( AddParameterHelper* add_parameter_helper );

        AddParameter& operator()( const LuaNil& nil );
        AddParameter& operator()( const LuaGlobalEnvironment& global_environment );
        AddParameter& operator()( const LuaValue& value );
        AddParameter& operator()( bool value );
        AddParameter& operator()( int value );
        AddParameter& operator()( float value );
        AddParameter& operator()( const char* value );
        AddParameter& operator()( const std::string& value );
        AddParameter& copy_values_from_stack( int begin, int end );

        void end();
        void end( bool* return_value );
        void end( int* return_value );
        void end( float* return_value );
        void end( std::string* return_value );
        void end( void** return_value );
        template <class Type> void end( Type* return_value );
        
        template <typename Type> AddParameter& operator()( const Type& value );
};

}

}

#endif
