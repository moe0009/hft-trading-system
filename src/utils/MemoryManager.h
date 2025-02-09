// memorymanager.h
// author: mohammad bazrouk
// provides numa‑aware, zero‑allocation memory management routines for critical paths.
#pragma once

#include <cstddef>

namespace hft {
namespace memory {

class memorymanager {
public:
    // allocate memory with specified alignment; in production, integrate with numa‑aware allocators
    static void* allocate(size_t size, size_t alignment);

    // free allocated memory
    static void deallocate(void* ptr);
};

} // namespace memory
} // namespace hft
