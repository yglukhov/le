//
// LuaFileReader.hpp
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

#ifndef SWEET_LUA_LUAFILEREADER_HPP_INCLUDED
#define SWEET_LUA_LUAFILEREADER_HPP_INCLUDED

#include "declspec.hpp"
#include "lua_/lua.h"
#include <fstream>
#include <vector>

namespace sweet
{

namespace lua
{

/**
// @internal
//
// An implementation of the lua_Reader function and its associated context
// that reads from a std::ifstream.
*/
class SWEET_LUA_DECLSPEC LuaFileReader
{
    std::ifstream       file_;
    int                 block_size_;
    std::vector<char>   block_;

    public:
        LuaFileReader( const char* filename, int block_size = 4096 );
        const char* read( size_t* size );
        static const char* reader( lua_State* lua, void* context, size_t* size );
};

}

}

#endif
