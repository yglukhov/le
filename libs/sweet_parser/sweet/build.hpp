//
// build.hpp
// Copyright (c) 2008 - 2011 Charles Baker.  All rights reserved.
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

#ifndef SWEET_BUILD_HPP_INCLUDED
#define SWEET_BUILD_HPP_INCLUDED

//
// If the BUILD_LIBRARY_SUFFIX macro isn't defined assume that the Sweet Build
// System is not being used to compile whatever is including this file and 
// make a guess at the correct values for BUILD_LIBRARY_SUFFIX and which 
// variant is being compiled based on whether or not the _DEBUG macro is 
// defined.
//
#ifndef BUILD_LIBRARY_SUFFIX
#ifdef _DEBUG
#define BUILD_VARIANT_DEBUG
#define BUILD_LIBRARY_SUFFIX "_msvc_debug.lib"
#else
#define BUILD_VARIANT_RELEASE
#define BUILD_LIBRARY_SUFFIX "_msvc_release.lib"
#endif
#endif

//
// Define macros for all components based on the variant that is being 
// built.
//
#if defined(BUILD_VARIANT_DEBUG)
#define SWEET_ASSERT_ENABLED
#define SWEET_EXCEPTIONS_ENABLED
#define SWEET_RTTI_ENABLED
#define SWEET_MEMORY_ENABLED
#define SWEET_MEMORY_TRACING_ENABLED
#define SWEET_POINTER_THREAD_SAFETY_ENABLED

#elif defined(BUILD_VARIANT_DEBUG_DLL)
#define SWEET_ASSERT_ENABLED
#define SWEET_EXCEPTIONS_ENABLED
#define SWEET_RTTI_ENABLED
#define SWEET_POINTER_THREAD_SAFETY_ENABLED

#elif defined(BUILD_VARIANT_RELEASE)
#define NDEBUG
#define SWEET_ASSERT_ENABLED
#define SWEET_EXCEPTIONS_ENABLED
#define SWEET_RTTI_ENABLED
#define SWEET_MEMORY_ENABLED
#define SWEET_POINTER_THREAD_SAFETY_ENABLED

#elif defined(BUILD_VARIANT_RELEASE_DLL)
#define NDEBUG
#define SWEET_ASSERT_ENABLED
#define SWEET_EXCEPTIONS_ENABLED
#define SWEET_RTTI_ENABLED
#define SWEET_POINTER_THREAD_SAFETY_ENABLED

#elif defined(BUILD_VARIANT_SHIPPING)
#define NDEBUG
#define SWEET_DEBUG_DUMP_ENABLED
#define SWEET_EXCEPTIONS_ENABLED
#define SWEET_RTTI_ENABLED
#define SWEET_MEMORY_ENABLED
#define SWEET_POINTER_THREAD_SAFETY_ENABLED

#elif defined(BUILD_VARIANT_SHIPPING_DLL)
#define NDEBUG
#define SWEET_DEBUG_DUMP_ENABLED
#define SWEET_EXCEPTIONS_ENABLED
#define SWEET_RTTI_ENABLED
#define SWEET_POINTER_THREAD_SAFETY_ENABLED

#endif

#endif
