#ifndef __FIR_INCLUDE_CHARTRAITS_H__
#define __FIR_INCLUDE_CHARTRAITS_H__

#include "Fir/Core/Typedefs.h"

namespace Fir
{
    template<typename CharType>
    class FIR_API CharTraits
    {
    public:
        /**
         * Calculates the length of the string.
        */
        static size_t Length(const CharType* p_str);

        /**
          * Copies the source string to the memory address pointed by destination.
        */
        static CharType* Copy(CharType* p_dest, const CharType* p_src);

        /**
         * Appends the source string onto the end of the destination string.
        */
        static CharType* Append(CharType* p_dest, const CharType* p_src);

        /**
         * Tests whether the two specified strings are equal.
        */
        static bool Equal(const CharType* p_str1, const CharType* p_str2);

        /**
         * Searches for the character specified.
         * Returns a null pointer if the character isn't found.
        */
        static CharType* Find(CharType* p_str, const CharType p_char);

    public:
        static const CharType NULL_CHAR = static_cast<CharType>('\0');
    };
}

#endif      // CharTraits.h