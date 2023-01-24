#include "Fir/Core/StringUtils.h"
#include <string.h>

namespace Fir
{
    Fir::String ToString(bool boolean)
    {
        return boolean ? "true" : "false";
    }

    Fir::String ToString(nullptr_t)
    {
        constexpr size_t bufferSize = (sizeof(void*) * 2) + 2;
        char buffer[bufferSize];

        memset(buffer, '0', bufferSize - 1);
        buffer[1] = 'x';            // 0x0000000000000000
        buffer[bufferSize - 1] = '\0';

        return buffer;
    }

    Fir::String ToString(void* ptr)
    {
        size_t i = 0;
        const ptrdiff_t base = 16;           // Base 16 = Hexadecimal

        ptrdiff_t castPtr = (ptrdiff_t)ptr;
        char buffer[(sizeof(void*) * 2) + 2] = { 0 };

        while (i++ < sizeof(void*) * 2)
        {
            buffer[i++] = "0123456789abcdef"[castPtr % base];

            if (castPtr)
                castPtr /= base;
        }

        buffer[i++] = 'x';
        buffer[i++] = '0';

        return Fir::String(buffer).Reverse();
    }
}