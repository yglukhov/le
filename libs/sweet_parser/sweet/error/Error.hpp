//
// Error.hpp
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

#ifndef SWEET_ERROR_ERROR_HPP_INCLUDED
#define SWEET_ERROR_ERROR_HPP_INCLUDED

#include "declspec.hpp"
#include "macros.hpp"
#include <exception>
#include <stdarg.h>

namespace sweet
{

namespace error
{

/**
// Base class for errors.
*/
class SWEET_ERROR_DECLSPEC Error : virtual public std::exception
{
    int error_;
    char text_ [1024];

    public:
        explicit Error( int error );
        Error( int error, const char* format, ... );
        virtual ~Error() throw ();
        int error() const;
        const char* what() const throw ();
        static const char* format( int oserror, char* buffer, unsigned int length );

    protected:
        void append( const char* format, va_list args );
        void append( const char* text );
};

}

}

#endif
