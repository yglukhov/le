//
// boost_integration.cpp
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

#include "stdafx.hpp"
#include <sweet/build.hpp>
#include <sweet/assert/assert.hpp>

#ifndef SWEET_EXCEPTIONS_ENABLED

namespace std
{
    class exception;
}

namespace boost
{

/**
// @internal
//
// Override the boost::throw_exception() function that is called instead of 
// throwing exceptions by the Boost Libraries when exceptions are disabled.
//
// @param exception
//  The std::exception that describes the error that has occured.
*/
void boost::throw_exception( const std::exception& exception )
{
    sweet::error::error( exception );
}

}

#endif
