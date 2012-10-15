//
// AddMember.hpp
// Copyright (c) 2007 - 2011 Charles Baker.  All rights reserved.
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

#ifndef SWEET_LUA_ADDMEMBER_HPP_INCLUDED
#define SWEET_LUA_ADDMEMBER_HPP_INCLUDED

#include "declspec.hpp"
#include "LuaNil.hpp"
#include "LuaGlobalEnvironment.hpp"
#include "AddGlobal.hpp"
#include "AddMember.hpp"
#include <sweet/rtti/Type.hpp>
#include <string>

namespace sweet
{

namespace lua
{

class AddMemberHelper;
class LuaObject;

/**
// A helper that provides a convenient syntax for adding member variables to
// objects.
*/
class SWEET_LUA_DECLSPEC AddMember
{
    AddMemberHelper* add_member_helper_;

    public:
        AddMember( AddMemberHelper* add_member_helper );
        ~AddMember();

        AddMember& this_pointer( void* value );
        AddMember& type( const rtti::Type& type );
        template <class Type> AddMember& metatable( const Type& object );

        AddMember& operator()( const char* name, const LuaNil& nil );
        AddMember& operator()( const char* name, const LuaGlobalEnvironment& global_environment );
        AddMember& operator()( const char* name, bool value );
        AddMember& operator()( const char* name, int value );
        AddMember& operator()( const char* name, float value );
        AddMember& operator()( const char* name, const char* value );
        AddMember& operator()( const char* name, const std::string& value );

        template <class Type> AddMember& operator()( const char* name, const Type& value );
        template <class Function, class P0> AddMember& operator()( const char* name, const Function& function, const P0& p0 );
        template <class Function, class P0, class P1> AddMember& operator()( const char* name, const Function& function, const P0& p0, const P1& p1 );
        template <class Function, class P0, class P1, class P2> AddMember& operator()( const char* name, const Function& function, const P0& p0, const P1& p1, const P2& p2 );
        template <class Function, class P0, class P1, class P2, class P3> AddMember& operator()( const char* name, const Function& function, const P0& p0, const P1& p1, const P2& p2, const P3& p3 );
        template <class Function, class P0, class P1, class P2, class P3, class P4> AddMember& operator()( const char* name, const Function& function, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4 );
        template <class Function, class P0, class P1, class P2, class P3, class P4, class P5> AddMember& operator()( const char* name, const Function& function, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5 );
        template <class Function, class P0, class P1, class P2, class P3, class P4, class P5, class P6> AddMember& operator()( const char* name, const Function& function, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6 );

        template <class Function, int POLICY> AddMember& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& value );
        template <class Function, int POLICY, class P0> AddMember& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0 );
        template <class Function, int POLICY, class P0, class P1> AddMember& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1 );
        template <class Function, int POLICY, class P0, class P1, class P2> AddMember& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1, const P2& p2 );
        template <class Function, int POLICY, class P0, class P1, class P2, class P3> AddMember& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3 );
        template <class Function, int POLICY, class P0, class P1, class P2, class P3, class P4> AddMember& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4 );
        template <class Function, int POLICY, class P0, class P1, class P2, class P3, class P4, class P5> AddMember& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5 );
        template <class Function, int POLICY, class P0, class P1, class P2, class P3, class P4, class P5, class P6> AddMember& operator()( const char* name, const LuaPolicyWrapper<Function, POLICY>& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6 );

        AddMember& operator()( const char* name, const LuaRawWrapper& value );
        template <class P0> AddMember& operator()( const char* name, const LuaRawWrapper& policy_wrapper, const P0& p0 );
        template <class P0, class P1> AddMember& operator()( const char* name, const LuaRawWrapper& policy_wrapper, const P0& p0, const P1& p1 );
        template <class P0, class P1, class P2> AddMember& operator()( const char* name, const LuaRawWrapper& policy_wrapper, const P0& p0, const P1& p1, const P2& p2 );
        template <class P0, class P1, class P2, class P3> AddMember& operator()( const char* name, const LuaRawWrapper& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3 );
        template <class P0, class P1, class P2, class P3, class P4> AddMember& operator()( const char* name, const LuaRawWrapper& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4 );
        template <class P0, class P1, class P2, class P3, class P4, class P5> AddMember& operator()( const char* name, const LuaRawWrapper& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5 );
        template <class P0, class P1, class P2, class P3, class P4, class P5, class P6> AddMember& operator()( const char* name, const LuaRawWrapper& policy_wrapper, const P0& p0, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6 );
};

}

}

#endif
