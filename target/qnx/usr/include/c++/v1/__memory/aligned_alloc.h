//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___MEMORY_ALIGNED_ALLOC_H
#define _LIBCPP___MEMORY_ALIGNED_ALLOC_H

#include <__config>
#include <cstddef>
#include <cstdlib>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

#ifndef _LIBCPP_HAS_NO_LIBRARY_ALIGNED_ALLOCATION

// Low-level helpers to call the aligned allocation and deallocation functions
// on the target platform. This is used to implement libc++'s own memory
// allocation routines -- if you need to allocate memory inside the library,
// chances are that you want to use `__libcpp_allocate` instead.
//
// Returns the allocated memory, or `nullptr` on failure.
void* __libcpp_aligned_alloc(std::size_t __alignment, std::size_t __size);
void __libcpp_aligned_free(void* __ptr);

#endif // !_LIBCPP_HAS_NO_LIBRARY_ALIGNED_ALLOCATION

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___MEMORY_ALIGNED_ALLOC_H
