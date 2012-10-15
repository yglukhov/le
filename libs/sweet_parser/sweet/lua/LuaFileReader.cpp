//
// LuaFileReader.cpp
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

#include "LuaFileReader.hpp"
#include "Error.hpp"
#include <sweet/assert/assert.hpp>

using namespace sweet::lua;

/**
// Constructor.
//
// @param filename
//  The name of the file to read blocks from.
//
// @param block_size
//  The number of bytes in a block.
*/
LuaFileReader::LuaFileReader( const char* filename, int block_size )
: file_( filename, std::ios::binary ),
  block_size_( block_size ),
  block_( block_size, 0 )
{
    if ( !file_.is_open() )
    {
        SWEET_ASSERT( filename );
        SWEET_ERROR( OpeningFileFailedError("Opening '%s' failed", filename) );
    }
}

/**
// Read another block from this LuaFileReader's stream.
//
// @param size
//  A variable to receive the number of bytes in the block that is read
//  in.
//
// @return
//  A pointer to the begining of the block.
*/
const char* LuaFileReader::read( size_t* size )
{
    SWEET_ASSERT( size );
    file_.read( &block_[0], block_size_ );
    *size = static_cast<size_t>( file_.gcount() );
    return *size > 0 ? &block_[0] : NULL;
}

/**
// Read from this LuaFileReader.
//
// @param lua_state
//  The lua_State.
//
// @param context
//  A pointer to the LuaFileReader that contains the context information for 
//  this call.
//
// @param size
//  A variable to receive the number of bytes in the block that is read
//  in.
*/
const char* LuaFileReader::reader( lua_State* lua_state, void* context, size_t* size )
{
    SWEET_ASSERT( context );
    LuaFileReader* reader = reinterpret_cast<LuaFileReader*>( context );
    return reader->read( size );
}
