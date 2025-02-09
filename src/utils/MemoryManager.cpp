// memorymanager.cpp
// author: mohammad bazrouk
// implements memory allocation routines using aligned allocations.
#include "MemoryManager.h"
#include <cstdlib>

namespace hft {
namespace memory {

void* memorymanager::allocate(size_t size, size_t alignment) {
    void *ptr = nullptr;
#if defined(_MSC_VER)
    ptr = _aligned_malloc(size, alignment);
#else
    if (posix_memalign(&ptr, alignment, size) != 0) {
        ptr = nullptr;
    }
#endif
    return ptr;
}

void memorymanager::deallocate(void* ptr) {
#if defined(_MSC_VER)
    _aligned_free(ptr);
#else
    std::free(ptr);
#endif
}

} // namespace memory
} // namespace hft
