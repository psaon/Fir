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

       /**
        * Copies the source string to the memory address pointed by destination.
       */
        static CharType* Copy(CharType* dest, const CharType* source);

    public:
        static const CharType NULL_CHAR = static_cast<CharType>('\0');

    };
}

#endif      // CharTraits.h