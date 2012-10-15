//
// LuaMemoryReader.cpp
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

#include "LuaMemoryReader.hpp"
#include <sweet/assert/assert.hpp>

using namespace sweet::lua;

/**
// Constructor.
//
// @param first
//  The first character in the script.
//
// @param last
//  One past the last character in the script.
*/
LuaMemoryReader::LuaMemoryReader( const char* first, const char* last )
: first_( first ),
  last_( last )
{
}

/**
// Read another block from this LuaMemoryReader's stream.
//
// @param size
//  A variable to receive the number of bytes in the block that is read
//  in.
//
// @return
//  A pointer to the begining of the block.
*/
const char* LuaMemoryReader::read( size_t* size )
{
    SWEET_ASSERT( size );
    *size = last_ - first_;

    const char* current = first_;
    first_ += (last_ - first_);
    return current;
}

/**
// @param lua
//  The lua_State.
//
// @param context
//  A pointer to the LuaMemoryReader that contains the context information for 
//  this call.
//
// @param size
//  A variable to receive the number of bytes in the block that is read
//  in.
//
// @return
//  A pointer to the begining of the block.
*/
const char* LuaMemoryReader::reader( lua_State* lua, void* context, size_t* size )
{
    SWEET_ASSERT( context );
    LuaMemoryReader* reader = reinterpret_cast<LuaMemoryReader*>( context );
    return reader->read( size );
}
