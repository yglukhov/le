//
// ParserAction.cpp
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
#include "ParserAction.hpp"

using namespace sweet::parser;

/**
// Constructor.
//
// @param index
//  The index of this action.
//
// @param identifier
//  The identifier of this action.
*/
ParserAction::ParserAction( int index, const std::string& identifier )
: index_( index ),
  identifier_( identifier )
{
}

/**
// Get the index of this action.
//
// @return
//  The index.
*/
int ParserAction::get_index() const
{
    return index_;
}

/**
// Get the identifier of this action.
//
// @return
//  The identifier.
*/
const std::string& ParserAction::get_identifier() const
{
    return identifier_;
}
