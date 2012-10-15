//
// ErrorPolicy.cpp
// Copyright (c) 2001 - 2012 Charles Baker.  All rights reserved.
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
#include "ErrorPolicy.hpp"

using namespace sweet::error;

/**
// Constructor.
*/
ErrorPolicy::ErrorPolicy()
{
}

/**
// Destructor.
*/
ErrorPolicy::~ErrorPolicy()
{
}

/**
// Handle an error.
//
// @param error
//  The Error object that describes the error that has occured.
*/
void ErrorPolicy::error( const Error& error )
{
}

/**
// Handle a std::exception.
//
// @param exception
//  The std::exception object that describes the error that has occured.
*/
void ErrorPolicy::error( const std::exception& exception )
{
}
