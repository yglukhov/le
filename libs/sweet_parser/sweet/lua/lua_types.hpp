//
// lua_types.hpp
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

#ifndef SWEET_LUA_TYPES_HPP_INCLUDED
#define SWEET_LUA_TYPES_HPP_INCLUDED

#include "declspec.hpp"

namespace sweet
{

namespace lua
{

SWEET_LUA_DECLSPEC extern const char* THIS_KEYWORD;
SWEET_LUA_DECLSPEC extern const char* METATABLE_KEYWORD;
SWEET_LUA_DECLSPEC extern const char* TYPE_KEYWORD;
SWEET_LUA_DECLSPEC extern const char* WEAK_OBJECTS_KEYWORD;
SWEET_LUA_DECLSPEC extern const char* PTR_KEYWORD;
SWEET_LUA_DECLSPEC extern const char* PREFIX_KEYWORD;
SWEET_LUA_DECLSPEC extern const char* SUFFIX_KEYWORD;
SWEET_LUA_DECLSPEC extern const char* PRE_LITERAL_KEYWORD;
SWEET_LUA_DECLSPEC extern const char* POST_LITERAL_KEYWORD;
SWEET_LUA_DECLSPEC extern const char* PRE_EXPRESSION_KEYWORD;
SWEET_LUA_DECLSPEC extern const char* POST_EXPRESSION_KEYWORD;

}

}

#endif
