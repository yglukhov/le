//
// LuaThread.ipp
// Copyright (c) 2009 - 2010 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_LUATHREAD_IPP_INCLUDED
#define SWEET_LUA_LUATHREAD_IPP_INCLUDED

namespace sweet
{

namespace lua
{

/**
// Call a member function in this %LuaThread.
//
// @param function
//  The name of the function to call.
//
// @param object
//  The object to call the member function on.
//
// @return
//  An %AddParameter helper that provides a convenient syntax for pushing
//  parameters to, calling, and retrieving return values from the function.
*/
template <class Type>
AddParameter LuaThread::call( const char* function, const Type& object )
{
    SWEET_ASSERT( function );
    return add_parameter_helper_.call<Type>( function, object );
}

/**
// Resume a member function in this %LuaThread.
//
// @param function
//  The name of the function to call.
//
// @param object
//  The object to call the member function on.
//
// @return
//  An %AddParameter helper that provides a convenient syntax for pushing
//  parameters to, calling, and retrieving return values from the function.
*/
template <class Type>
AddParameter LuaThread::resume( const char* function, const Type& object )
{
    SWEET_ASSERT( function );
    return add_parameter_helper_.resume<Type>( function, object );
}

}

}

#endif
