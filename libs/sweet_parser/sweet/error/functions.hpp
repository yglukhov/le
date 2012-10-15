//
// error_functions.hpp
// Copyright (c) 2001 - 2011 Charles Baker.  All rights reserved.
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

#ifndef SWEET_ERROR_FUNCTIONS_HPP_INCLUDED
#define SWEET_ERROR_FUNCTIONS_HPP_INCLUDED

#include "declspec.hpp"

namespace std
{

class exception;

}

namespace sweet
{

namespace error
{

class Error;
class ErrorPolicy;

SWEET_ERROR_DECLSPEC void set_error_policy( ErrorPolicy* error_policy );
SWEET_ERROR_DECLSPEC ErrorPolicy* get_error_policy();
SWEET_ERROR_DECLSPEC void error( const Error& error );
SWEET_ERROR_DECLSPEC void error( const std::exception& exception );

}

}

#endif
