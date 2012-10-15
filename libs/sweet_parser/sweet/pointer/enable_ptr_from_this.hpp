//
// enable_ptr_from_this.hpp
// Copyright (c) 2009 - 2012 Charles Baker.  All rights reserved.
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

#ifndef SWEET_POINTER_ENABLE_PTR_FROM_THIS_HPP_INCLUDED
#define SWEET_POINTER_ENABLE_PTR_FROM_THIS_HPP_INCLUDED

#include <sweet/build.hpp>
#include <sweet/assert/assert.hpp>
#include "ptr.hpp"
#include "weak_ptr.hpp"

namespace sweet
{

namespace pointer
{

/**
// A base class to allow construction of a ptr<> from a raw pointer.
*/
template <class Type>
class enable_ptr_from_this
{
    protected:
        enable_ptr_from_this()
        : weak_this_()
        {
        }
        
        enable_ptr_from_this( const enable_ptr_from_this& )
        : weak_this_()
        {
        }
        
        enable_ptr_from_this& operator=( const enable_ptr_from_this& )
        {
            return *this;
        }
        
        ~enable_ptr_from_this()
        {
        }
    
    public:
        ptr<Type> ptr_from_this()
        {
            ptr<Type> ptr( weak_this_ );
            SWEET_ASSERT( ptr.get() == this );
            return ptr;
        }

        ptr<const Type> ptr_from_this() const
        {
            ptr<const Type> ptr( weak_this_ );
            SWEET_ASSERT( ptr.get() == this );
            return ptr;
        }

        mutable weak_ptr<Type> weak_this_;
};

}

using pointer::enable_ptr_from_this;

}

#endif
