//
// RegexCharacter.cpp
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
#include "RegexCharacter.hpp"
#include <sweet/assert/assert.hpp>

using namespace sweet::lexer;

/**
// Constructor.
//
// @param begin_character
//  The first character in the represented interval.
//
// @param end_character
//  One past the last character in the represented interval.
*/
RegexCharacter::RegexCharacter( int begin_character, int end_character )
: begin_character_( begin_character ),
  end_character_( end_character )
{
    SWEET_ASSERT( begin_character_ < end_character_ );
}

/**
// Get the first character in the represented interval.
//
// @return
//  The begin character.
*/
int RegexCharacter::get_begin_character() const
{
    return begin_character_;
}


/**
// Get the character one past the last character in the represented interval.
//
// @return
//  The end character.
*/
int RegexCharacter::get_end_character() const
{
    return end_character_;
}


/**
// Less than operator.
//
// @param regex_character
//  The character to compare with.
//
// @return
//  True if the end of the interval represented by this character is less 
//  than the beginning of the interval represented by \e regex_character.
*/
bool RegexCharacter::operator<( const RegexCharacter& regex_character ) const
{
    return end_character_ < regex_character.begin_character_;
}
