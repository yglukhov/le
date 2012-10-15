//
// ErrorTemplate.ipp
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

#ifndef SWEET_ERROR_ERRORTEMPLATE_IPP_INCLUDED
#define SWEET_ERROR_ERRORTEMPLATE_IPP_INCLUDED

#include <stdarg.h>
#include "ErrorTemplate.hpp"

namespace sweet
{

namespace error
{

/**
// Constructor.
//
// @param format
//  A printf style format string that describes the error.
//
// @param ...
//  Parameters as described by \e format.
*/
template <int ERRNO, class Base>
ErrorTemplate<ERRNO, Base>::ErrorTemplate( const char* format, ... )
: Base( ERRNO )
{
    va_list args;
    va_start( args, format );
    Error::append( format, args );
    va_end( args );
}

/**
// Constructor.
//
// @param format
//  A printf style format string that describes the error.
//
// @param args
//  Parameters as described by \e format.
*/
template <int ERRNO, class Base> 
ErrorTemplate<ERRNO, Base>::ErrorTemplate( const char* format, va_list args )
: Base( ERRNO )
{
    Error::append( format, args );
}

}

}

#endif
