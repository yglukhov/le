//
// lua_types.cpp
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

#include "lua_types.hpp"

/** 
// @internal
//
// The keyword used to store the this %pointer for LuaObjects. 
*/
const char* sweet::lua::THIS_KEYWORD = "__this";

/** 
// @internal
//
// The keyword used to store the metatable used to redirect calls on 
// %LuaObject tables to their prototype tables. 
*/
const char* sweet::lua::METATABLE_KEYWORD = "__metatable";

/** 
// @internal
//
// The keyword used to store the type of a %LuaObject.
*/
const char* sweet::lua::TYPE_KEYWORD = "__type";

/** 
// @internal
//
// The keyword used to store the weak objects table in the %Lua registry.
*/
const char* sweet::lua::WEAK_OBJECTS_KEYWORD = "__weak_objects";

/** 
// @internal
//
// The keyword used to store smart pointers for LuaObjects.
*/
const char* sweet::lua::PTR_KEYWORD = "__ptr";

/** 
// @internal
//
// The keyword used to start a Lua block in a preprocessed file.
*/
const char* sweet::lua::PREFIX_KEYWORD = "<?lua";

/** 
// @internal
//
// The keyword used to end a Lua block in a preprocessed file.
*/
const char* sweet::lua::SUFFIX_KEYWORD = "?>";

/** 
// @internal
//
// The text emitted to start a literal block in the postprocessed output.
*/
const char* sweet::lua::PRE_LITERAL_KEYWORD = "io.write([[";

/** 
// @internal
//
// The text emitted to end a literal block in the postprocessed output.
*/
const char* sweet::lua::POST_LITERAL_KEYWORD = "]])";

/**
// @internal
//
// The text emitted to start a literal block in the postprocessed output.
*/
const char* sweet::lua::PRE_EXPRESSION_KEYWORD = "io.write(tostring(";

/** 
// @internal
//
// The text emitted to end a literal block in the postprocessed output.
*/
const char* sweet::lua::POST_EXPRESSION_KEYWORD = "))";