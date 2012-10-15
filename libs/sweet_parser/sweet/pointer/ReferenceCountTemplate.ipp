//
// ReferenceCountTemplate.ipp
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

#ifndef SWEET_POINTER_REFERENCECOUNTTEMPLATE_IPP_INCLUDED
#define SWEET_POINTER_REFERENCECOUNTTEMPLATE_IPP_INCLUDED

#include "ReferenceCountTemplate.hpp"

namespace sweet
{

namespace pointer
{

/**
// Constructor.
//
// @param object
//  The object to count references for.
//
// @param deleter
//  The functor to use to delete \e object when its reference count drops to
//  0.
*/
template <class Type, class Deleter> ReferenceCountTemplate<Type, Deleter>::ReferenceCountTemplate( Type* object, Deleter deleter )
: ReferenceCount(),
  object_( object ),
  deleter_( deleter )
{
}

/**
// Destroy the object that this ReferenceCountTemplate is counting references
// to.
*/
template <class Type, class Deleter> void ReferenceCountTemplate<Type, Deleter>::dispose()
{
    SWEET_ASSERT( object_ );
    deleter_( object_ );
    object_ = 0;
}

/**
// Destroy this ReferenceCountTemplate object.
*/
template <class Type, class Deleter> void ReferenceCountTemplate<Type, Deleter>::destroy()
{
    delete this;
}

/**
// Default deleter for reference counted pointers.
//
// @param object
//  The object to delete.
//
// @relates ReferenceCountTemplate.
*/
template <class Type> void default_deleter( Type* object )
{
    delete object;
}

}

}

#endif
