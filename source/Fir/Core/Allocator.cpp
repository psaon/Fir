#include "Fir/Core/Allocator.h"
#include <stdlib.h>

namespace Fir
{
    void* _FIR Allocator::Allocate(size_t p_size)
    {
        return malloc(p_size);
    }

    void* _FIR Allocator::Reallocate(void* p_buffer, size_t p_size)
    {
        return realloc(p_buffer, p_size);
    }

    void _FIR Allocator::Free(void* p_buffer)
    {
        free(p_buffer);
    }
}