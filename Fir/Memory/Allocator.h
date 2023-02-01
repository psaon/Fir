#ifndef __FIR_MEMORY_ALLOCATOR_H__
#define __FIR_MEMORY_ALLOCATOR_H__

#include "Fir/Core/Core.h"

namespace Fir
{
    class FIR_API Allocator
    {
    public:
        FIR_NODISCARD void* Allocate(size_t p_size);
        FIR_NODISCARD void* Reallocate(void* p_buffer, size_t p_size);
        void Free(void* p_buffer);
    };
}

#endif      // Allocator.h