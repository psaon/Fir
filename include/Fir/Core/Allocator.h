#ifndef __FIR_INCLUDE_ALLOCATOR_H__
#define __FIR_INCLUDE_ALLOCATOR_H__

#include "Fir/Core/Typedefs.h"

namespace Fir
{
    class FIR_API Allocator
    {
    public:
        void* Allocate(size_t p_size);
        void* Reallocate(void* p_buffer, size_t p_size);
        void Free(void* p_buffer);
    };
}

#endif