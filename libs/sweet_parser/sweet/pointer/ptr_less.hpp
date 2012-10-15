//
// ptr_less.hpp
// Copyright (c) 2007 - 2012 Charles Baker.  All rights reserved.
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

#ifndef SWEET_POINTER_PTR_LESS_HPP_INCLUDED
#define SWEET_POINTER_PTR_LESS_HPP_INCLUDED

namespace sweet
{

namespace pointer
{

template <class Type> class ptr;

/**
// Compare objects through two ptrs.
*/
template <class Type>
class ptr_less
{
    public:
        bool operator()( const ptr<Type>& lhs, const ptr<Type>& rhs ) const
        {
            return *lhs < *rhs;
        }
};

}

using pointer::ptr_less;

}

#endif
