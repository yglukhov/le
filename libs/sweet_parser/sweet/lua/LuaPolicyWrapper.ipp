//
// LuaPolicyWrapper.ipp
// Copyright (c) 2008 - 2010 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_LUAPOLICYWRAPPER_IPP_INCLUDED
#define SWEET_LUA_LUAPOLICYWRAPPER_IPP_INCLUDED

#include "LuaPolicyWrapper.hpp"
#include <sweet/assert/assert.hpp>

namespace sweet
{

namespace lua
{

/**
// Constructor.
//
// @param function
//  The address of the function that this LuaPolicyWrapper is wrapping.
*/
template <class Function, int POLICY>
LuaPolicyWrapper<Function, POLICY>::LuaPolicyWrapper( Function function )
: function_( function )
{
    SWEET_ASSERT( function_ );
}

/**
// Get the address of the function that this LuaPolicyWrapper is wrapping.
//
// @return
//  The address of the function that this LuaPolicyWrapper is wrapping.
*/
template <class Function, int POLICY>
Function LuaPolicyWrapper<Function, POLICY>::get_function() const
{
    SWEET_ASSERT( function_  );
    return function_;
}

}

}

#endif
