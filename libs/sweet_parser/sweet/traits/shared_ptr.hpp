//
// shared_ptr.hpp
// Copyright (c) 2009 Charles Baker.  All rights reserved.
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

#ifndef SWEET_TRAITS_TRAITS_SHARED_PTR_HPP_INCLUDED
#define SWEET_TRAITS_TRAITS_SHARED_PTR_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

namespace sweet
{

namespace traits
{

template <class Type>
struct traits<boost::shared_ptr<Type>>
{
    typedef Type                     base_type;
    typedef boost::shared_ptr<Type>  value_type;
    typedef boost::shared_ptr<Type>& reference_type;
    typedef Type*                    pointer_type;
    typedef boost::shared_ptr<Type>  parameter_type;
    typedef boost::shared_ptr<Type>  return_value_type;
};


template <class Type>
struct traits<boost::shared_ptr<const Type>>
{
    typedef Type                           base_type;
    typedef boost::shared_ptr<const Type>  value_type;
    typedef boost::shared_ptr<const Type>& reference_type;
    typedef boost::shared_ptr<const Type>* pointer_type;
    typedef boost::shared_ptr<const Type>  parameter_type;
    typedef boost::shared_ptr<const Type>  return_value_type;
};


template <class Type>
struct traits<boost::weak_ptr<Type>>
{
    typedef Type                   base_type;
    typedef boost::weak_ptr<Type>  value_type;
    typedef boost::weak_ptr<Type>& reference_type;
    typedef Type*                  pointer_type;
    typedef boost::weak_ptr<Type>  parameter_type;
    typedef boost::weak_ptr<Type>  return_value_type;
};


template <class Type>
struct traits<boost::weak_ptr<const Type>>
{
    typedef Type                         base_type;
    typedef boost::weak_ptr<const Type>  value_type;
    typedef boost::weak_ptr<const Type>& reference_type;
    typedef boost::weak_ptr<const Type>* pointer_type;
    typedef boost::weak_ptr<const Type>  parameter_type;
    typedef boost::weak_ptr<const Type>  return_value_type;
};

}

}

#endif
