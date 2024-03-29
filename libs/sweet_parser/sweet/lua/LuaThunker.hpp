//
// LuaThunker.hpp
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

#ifndef SWEET_LUA_LUATHUNKER_HPP
#define SWEET_LUA_LUATHUNKER_HPP

#include "LuaReturner.hpp"

namespace sweet
{

namespace lua
{

/**
// @internal
//
// Thunk C++ functions called from Lua.
*/
template <class Function, class Returner = LuaReturner<typename traits::traits<Function>::return_type>, int P0 = 1, int P1 = 2, int P2 = 3, int P3 = 4, int P4 = 5, int P5 = 6, int P6 = 7>
struct LuaThunker
{
};

/**
// @internal
//
// Thunk functions with no arguments.
*/
template <class R, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
struct LuaThunker<R (*)(), Returner, P0, P1, P2, P3, P4, P5, P6>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk functions with one argument.
*/
template <class R, class A0, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
struct LuaThunker<R (*)(A0), Returner, P0, P1, P2, P3, P4, P5, P6>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk functions with two arguments.
*/
template <class R, class A0, class A1, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
struct LuaThunker<R (*)(A0, A1), Returner, P0, P1, P2, P3, P4, P5, P6>
{
    static int function( lua_State* lua_state );
};


/**
// @internal
//
// Thunk functions with three arguments.
*/
template <class R, class A0, class A1, class A2, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
struct LuaThunker<R (*)(A0, A1, A2), Returner, P0, P1, P2, P3, P4, P5, P6>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk functions with four arguments.
*/
template <class R, class A0, class A1, class A2, class A3, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
struct LuaThunker<R (*)(A0, A1, A2, A3), Returner, P0, P1, P2, P3, P4, P5, P6>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk functions with five arguments.
*/
template <class R, class A0, class A1, class A2, class A3, class A4, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
struct LuaThunker<R (*)(A0, A1, A2, A3, A4), Returner, P0, P1, P2, P3, P4, P5, P6>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk functions with six arguments.
*/
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
struct LuaThunker<R (*)(A0, A1, A2, A3, A4, A5), Returner, P0, P1, P2, P3, P4, P5, P6>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk member functions with no arguments.
*/
template <class R, class T, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(), Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk const member functions with no arguments.
*/
template <class R, class T, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)() const, Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk member functions with one argument.
*/
template <class R, class T, class A0, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0), Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk const member functions with one argument.
*/
template <class R, class T, class A0, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0) const, Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk member functions with two arguments.
*/
template <class R, class T, class A0, class A1, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0, A1), Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk const member functions with two arguments.
*/
template <class R, class T, class A0, class A1, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0, A1) const, Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk member functions with three arguments.
*/
template <class R, class T, class A0, class A1, class A2, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0, A1, A2), Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk const member functions with three arguments.
*/
template <class R, class T, class A0, class A1, class A2, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0, A1, A2) const, Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk member functions with four arguments.
*/
template <class R, class T, class A0, class A1, class A2, class A3, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0, A1, A2, A3), Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk const member functions with four arguments.
*/
template <class R, class T, class A0, class A1, class A2, class A3, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0, A1, A2, A3) const, Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk member functions with five arguments.
*/
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0, A1, A2, A3, A4), Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk const member functions with five arguments.
*/
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0, A1, A2, A3, A4) const, Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk member functions with six arguments.
*/
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0, A1, A2, A3, A4, A5), Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

/**
// @internal
//
// Thunk const member functions with six arguments.
*/
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
struct LuaThunker<R (T::*)(A0, A1, A2, A3, A4, A5) const, Returner, PT, P0, P1, P2, P3, P4, P5>
{
    static int function( lua_State* lua_state );
};

}

}

#endif
