//
// Error.hpp
// Copyright (c) 2008 - 2012 Charles Baker.  All rights reserved.
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

#ifndef SWEET_CMDLINE_ERROR_HPP_INCLUDED
#define SWEET_CMDLINE_ERROR_HPP_INCLUDED

#include "declspec.hpp"
#include <sweet/error/Error.hpp>
#include <sweet/error/ErrorTemplate.hpp>

namespace sweet
{

namespace cmdline
{

/**
// Error codes for exceptions thrown from the %cmdline library.
//
// @relates Error
*/
enum ErrorCodes
{
    CMDLINE_ERROR_NONE, ///< No error has occured.
    CMDLINE_ERROR_INVALID_OPTION, ///< An option on the command line is not recognized or expects an argument and is grouped with other options.
    CMDLINE_ERROR_INVALID_ARGUMENT ///< An option on the command line that requires an argument doesn't have one.
};

/**
// Errors thrown from the %cmdline library.
*/
class SWEET_CMDLINE_DECLSPEC Error : public error::Error 
{
    public:
        Error( int error );
};

/**
// An option on the command line is not recognized or expects an argument and 
// is grouped with other options.
//
// @relates Error
*/
typedef error::ErrorTemplate<CMDLINE_ERROR_INVALID_OPTION, Error> InvalidOptionError;

/**
// An option on the command line that requires an argument doesn't have 
// one.
//
// @relates Error
*/
typedef error::ErrorTemplate<CMDLINE_ERROR_INVALID_ARGUMENT, Error> InvalidArgumentError;

}

}

#endif
