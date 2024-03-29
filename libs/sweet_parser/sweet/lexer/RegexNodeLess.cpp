//
// RegexNodeLess.cpp
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
#include "RegexNodeLess.hpp"
#include "RegexNode.hpp"
#include <sweet/assert/assert.hpp>

using namespace sweet;
using namespace sweet::lexer;

/**
// Compare two RegexNodes.
//
// @param lhs
//  The first RegexNode to compare.
//
// @param rhs
//  The second RegexNode to compare.
//
// @return
//  True if the index of \e lhs is less than the index of \e rhs otherwise 
//  false.
*/
bool RegexNodeLess::operator()( const RegexNode* lhs, const RegexNode* rhs ) const
{
    SWEET_ASSERT( lhs );
    SWEET_ASSERT( rhs );
    return *lhs < *rhs;
}
