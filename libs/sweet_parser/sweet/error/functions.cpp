//
// error_functions.cpp
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
#include "Error.hpp"
#include "ErrorPolicy.hpp"
#include "functions.hpp"
#include <exception>
#include <stdio.h>
#include <stdlib.h>

using namespace sweet::error;

namespace sweet
{

namespace error
{

/**
// @internal
//
// The global ErrorPolicy that sweet::error::error() reports Errors to.
*/
static ErrorPolicy* sweet_error_policy = NULL;

/**
// Set the global ErrorPolicy.
//
// @param error_policy
//  The ErrorPolicy to set as the global ErrorPolicy or null to set the global
//  ErrorPolicy to nothing.
*/
void set_error_policy( ErrorPolicy* error_policy )
{
    sweet_error_policy = error_policy;
}

/**
// Get the global ErrorPolicy.
//
// @return
//  The global ErrorPolicy or null if the global ErrorPolicy hasn't been set.
*/
ErrorPolicy* get_error_policy()
{
    return sweet_error_policy;
}

/**
// Handle an error.
//
// Passes the error on to the global ErrorPolicy if one has been set otherwise
// prints the error description to stderr and calls ::exit() passing 
// EXIT_FAILURE as the return code to pass back to the operating system.
//
// @param error
//  The Error object that describes the error that has occured.
*/
void error( const Error& error )
{
    ErrorPolicy* error_policy = sweet::error::get_error_policy();
    if ( error_policy )
    {
        error_policy->error( error );
    }
    else
    {
        fputs( error.what(), stderr );
        fputs( ".\n", stderr );
        exit( EXIT_FAILURE );
    }
}

/**
// Handle an error.
//
// Passes the error on to the global ErrorPolicy if one has been set otherwise
// prints the error description to stderr and calls ::exit() passing 
// EXIT_FAILURE as the return code to pass back to the operating system.
//
// @param exception
//  The std::exception object that describes the error that has occured.
*/
void error( const std::exception& exception )
{
    ErrorPolicy* error_policy = sweet::error::get_error_policy();
    if ( error_policy )
    {
        error_policy->error( exception );
    }
    else
    {
        fputs( exception.what(), stderr );
        fputs( ".\n", stderr );
        exit( EXIT_FAILURE );
    }
}

}

}
