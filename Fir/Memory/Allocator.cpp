#include "Fir/Memory/Allocator.h"

#include <stdlib.h>     // For malloc, realloc, and free.
#include "Fir/Core/Exceptions.h"

namespace Fir
{
    void* _FIR Allocator::Allocate(size_t p_size)
    {
        void* ret = malloc(p_size);
        if (!ret) throw _FIR FailedAllocException();

        return ret;
    }

    void* _FIR Allocator::Reallocate(void* p_buffer, size_t p_size)
    {
        void* ret = realloc(p_buffer, p_size);
        if (!ret) throw _FIR FailedAllocException();

        return ret;
    }

    void _FIR Allocator::Free(void* p_buffer)
    {
        free(p_buffer);
    }
}