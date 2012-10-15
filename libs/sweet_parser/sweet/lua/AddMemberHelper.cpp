//
// AddMemberHelper.cpp
// Copyright (c) 2009 - 2011 Charles Baker.  All rights reserved.
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

#include "stdafx.hpp"
#include "lua_types.hpp"
#include "AddGlobal.hpp"
#include "AddParameter.hpp"
#include "AddMember.hpp"
#include "AddMemberHelper.hpp"
#include "AddParameterHelper.hpp"
#include "Lua.hpp"
#include <sweet/assert/assert.hpp>

using namespace sweet::lua;

AddMemberHelper::AddMemberHelper( Lua* lua )
: lua_( lua ),
  references_( 0 ),
  restore_to_position_( 0 )
{
    SWEET_ASSERT( lua_ );
}

lua_State* AddMemberHelper::get_lua_state() const
{
    SWEET_ASSERT( lua_ );
    return lua_->get_lua_state();
}

void AddMemberHelper::reference()
{
    if ( references_ == 0 )
    {
        SWEET_ASSERT( lua_ );
        restore_to_position_ = lua_gettop( lua_->get_lua_state() ) - 1;
    }

    ++references_;    
}

void AddMemberHelper::release()
{
    SWEET_ASSERT( references_ > 0 );

    --references_;
    if ( references_ == 0 )
    {
        SWEET_ASSERT( lua_ );
        lua_settop( lua_->get_lua_state(), restore_to_position_ );
        restore_to_position_ = 0;
    }
}
