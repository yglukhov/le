//
// AddParameter.ipp
// Copyright (c) 2007 - 2012 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_ADDPARAMETER_IPP_INCLUDED
#define SWEET_LUA_ADDPARAMETER_IPP_INCLUDED

#include "AddParameter.hpp"
#include "AddParameterHelper.hpp"

/**
// Push an arbitrary value onto the Lua stack.
//
// @param value
//  The value to push.
//
// @return
//  This AddParameter.
*/
template <typename Type> 
sweet::lua::AddParameter& sweet::lua::AddParameter::operator()( const Type& value )
{
    SWEET_ASSERT( add_parameter_helper_ );
    add_parameter_helper_->push<Type>( value );
    return *this;
}

/**
// Call the function and retrieve an arbitrary return value.
//
// This is done in this function instead of the destructor because calling 
// the function can throw an exception.
//
// @param return_value
//  A pointer to the variable to place the return value into (assumed not 
//  null).
*/
template <class Type> 
void sweet::lua::AddParameter::end( Type* return_value )
{
    SWEET_ASSERT( return_value );
    add_parameter_helper_->end<Type>( return_value );
}

#endif
