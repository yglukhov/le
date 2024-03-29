//
// ReferenceCount.cpp
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
#include "ReferenceCount.hpp"
#include <sweet/atomic/atomic.ipp>

using namespace sweet;
using namespace sweet::pointer;

/**
// Constructor.
*/
ReferenceCount::ReferenceCount()
: references_( 1 ),
  weak_references_( 1 )
{
}

/**
// Destructor.
*/
ReferenceCount::~ReferenceCount()
{
    SWEET_ASSERT( references_ == 0 );
    SWEET_ASSERT( weak_references_ == 0 );
}

/**
// Add a reference to this ReferenceCount.
*/
void ReferenceCount::reference()
{
    sweet::atomic::atomic_increment( &references_ );
}

/**
// Add a promoted reference to this ReferenceCount.
//
// This is called when a weak reference is promoted to a strong reference
// as happens when a ptr is created from a weak_ptr.  This reference addition
// needs to make sure that it isn't being added in between the reference count
// being decreased to 0 and the referenced object being deleted or the 
// reference count being increased (resulting in an incorrect reference
// count).
//
// @return
//  True if the reference was successfully promoted otherwise false because
//  the object has been destroyed.
*/
bool ReferenceCount::promote_reference()
{
//
// Loop until the number of references is 0 (in which case the object has been
// deleted) or the number of references is successfully incremented from the
// value that was just compared with (in which case a reference has been 
// successfully added without the reference count bouncing down to 0 in 
// between the comparison and the increment or the reference count being
// incremented).
//
    for ( ;; )
    {
        int references = static_cast<volatile const int&>( references_ );
        if ( references == 0 )
        {
            return false;
        }

        if ( sweet::atomic::atomic_compare_exchange(&references_, references + 1, references) == references )
        {
            return true;
        }
    }
}

/**
// Release a reference to this ReferenceCount.
*/
void ReferenceCount::release()
{
    if ( sweet::atomic::atomic_decrement(&references_) == 0 )
    {
        dispose();
        weak_release();
    }
}

/**
// Add a weak reference to this ReferenceCount.
*/
void ReferenceCount::weak_reference()
{
    sweet::atomic::atomic_increment( &weak_references_ );
}

/**
// Release a weak reference to this ReferenceCount.
*/
void ReferenceCount::weak_release()
{
    if ( sweet::atomic::atomic_decrement(&weak_references_) == 0 )
    {
        destroy();
    }
}
