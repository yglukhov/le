//
// ErrorTemplate.hpp
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

#ifndef SWEET_ERROR_ERRORTEMPLATE_HPP_INCLUDED
#define SWEET_ERROR_ERRORTEMPLATE_HPP_INCLUDED

#include <stdarg.h>

namespace sweet
{

namespace error
{

/**
// A class template for implementing Error derived classes.
*/
template <int ERRNO, class Base>
class ErrorTemplate : public Base
{
    public:
        ErrorTemplate( const char* format, ... );
        ErrorTemplate( const char* format, va_list args );
};

}

}

#include "ErrorTemplate.ipp"

#endif
