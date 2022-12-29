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

        /**
         * Appends the source string onto the end of the destination string.
        */
        static CharType* Append(CharType* dest, const CharType* source);

        /**
         * Tests whether the two specified strings are equal.
        */
        static bool Compare(const CharType* str1, const CharType* str2, size_t n);

        /**
         * Searches for the character specified.
         * Returns a null pointer if the character isn't found.
        */
        static CharType* Find(CharType* string, const CharType character);

    public:
        static const CharType NULL_CHAR = static_cast<CharType>('\0');
    };
}

#endif      // CharTraits.h