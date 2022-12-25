#ifndef __FIR_INCLUDE_CHARTRAITS_H__
#define __FIR_INCLUDE_CHARTRAITS_H__

#include "Fir/Core/Typedefs.h"

namespace Fir
{
    template<typename CharType>
    class CharTraits
    {
    public:
        /**
         * Calculates the length of the string.
        */
        static size_t Length(const CharType* string);
    };
}

#endif      // CharTraits.h