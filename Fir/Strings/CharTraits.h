#ifndef __FIR_STRINGS_CHARTRAITS_H__
#define __FIR_STRINGS_CHARTRAITS_H__

#include "Fir/Core/Core.h"

namespace Fir
{
    template<typename CharType>
    class FIR_API CharTraits
    {
    public:
        static CharType* Append(CharType* p_dest, const CharType* p_src);
        static CharType* Copy(CharType* p_dest, const CharType* p_src);
        static bool Equal(const CharType* p_str1, const CharType* p_str2);
        static CharType* Find(CharType* p_str, const CharType p_char);
        static size_t Length(const CharType* p_str);

    public:
        static const CharType NullChar = static_cast<CharType>(0);
        static constexpr size_t CharSize = sizeof(CharType);
    };
}

#endif      // CharTraits.h