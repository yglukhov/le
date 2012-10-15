//
// AddGlobal.hpp
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

#ifndef SWEET_LUA_ADDGLOBAL_HPP_INCLUDED
#define SWEET_LUA_ADDGLOBAL_HPP_INCLUDED

#include "declspec.hpp"
#include "lua_/lua.h"
#include <string>

namespace sweet
{

namespace lua
{

class LuaNil;
class LuaGlobalEnvironment;
class LuaObject;
class LuaRawWrapper;
template <class Function, int POLICY> class LuaPolicyWrapper;

/**
// A helper that provides a convenient syntax for setting global variables.
*/
class SWEET_LUA_DECLSPEC AddGlobal
{
    lua_State* lua_state_; ///< The lua_State to set global variables in.

    public:
        AddGlobal( lua_State* lua_state );

        AddGlobal& operator()( const char* name, const LuaNil& nil );
        AddGlobal& operator()( const char* name, const LuaGlobalEnvironment& global_environment );
        AddGlobal& operator()( const char* name, bool value );
        AddGlobal& operator()( const char* name, int value );
        AddGlobal& operator()( const char* name, float value );
        AddGlobal& operator()( const char* name, const char* value );
        AddGlobal& operator()( const char* name, const std::string& value );

        template <class Type> AddGlobal& operator()( const char* name, const Type& value );
        template <class Function, class P0> AddGlobal& operator()( const char* name, const Function& function, const P0& p0 );
        template <class Function, class P0, class P1> AddGlobal& operator()( const char* name, const Function& function, const P0& p0, const P1& p1 );
        template <class Function, class P0, class P1, class P2> AddGlobal& operator()( const char* name, const Function& function, const P0& p0, const P1& p1, const P2& p2 );
        template <class Function, class P0, class P1, class P2, class P3> AddGlobal& operator()( const char* name, const Function& function, const P0& p0, const P1& p1, const P2& p2, const P3& p3 );
        template <class Function, class P0, class P1, class P2, class P3, class P4> AddGlobal& operator()( const char* name, const Function& function, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4 );
        template <class Function, class P0, class P1, class P2, class P3, class P4, class P5> AddGlobal& operator()( const char* name, const Function& function, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5 );
        template <class Function, class P0, class P1, class P2, class P3, class P4, class P5, class P6> AddGlobal& operator()( const char* name, const Function& function, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6 );

        template <class Function, int POLICY> AddGlobal& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper );
        template <class Function, int POLICY, class P0> AddGlobal& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0 );
        template <class Function, int POLICY, class P0, class P1> AddGlobal& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1 );
        template <class Function, int POLICY, class P0, class P1, class P2> AddGlobal& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1, const P2& p2 );
        template <class Function, int POLICY, class P0, class P1, class P2, class P3> AddGlobal& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3 );
        template <class Function, int POLICY, class P0, class P1, class P2, class P3, class P4> AddGlobal& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4 );
        template <class Function, int POLICY, class P0, class P1, class P2, class P3, class P4, class P5> AddGlobal& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5 );
        template <class Function, int POLICY, class P0, class P1, class P2, class P3, class P4, class P5, class P6> AddGlobal& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6 );

        AddGlobal& operator()( const char* name, const LuaRawWrapper& raw_wrapper );
        template <class P0> AddGlobal& operator()( const char* name, const LuaRawWrapper& raw_wrapper, const P0& p0 );
        template <class P0, class P1> AddGlobal& operator()( const char* name, const LuaRawWrapper& raw_wrapper, const P0& p0, const P1& p1 );
        template <class P0, class P1, class P2> AddGlobal& operator()( const char* name, const LuaRawWrapper& raw_wrapper, const P0& p0, const P1& p1, const P2& p2 );
        template <class P0, class P1, class P2, class P3> AddGlobal& operator()( const char* name, const LuaRawWrapper& raw_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3 );
        template <class P0, class P1, class P2, class P3, class P4> AddGlobal& operator()( const char* name, const LuaRawWrapper& raw_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4 );
        template <class P0, class P1, class P2, class P3, class P4, class P5> AddGlobal& operator()( const char* name, const LuaRawWrapper& raw_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5 );
        template <class P0, class P1, class P2, class P3, class P4, class P5, class P6> AddGlobal& operator()( const char* name, const LuaRawWrapper& raw_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6 );
};

}

}

#endif
