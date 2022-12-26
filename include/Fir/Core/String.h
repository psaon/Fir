#ifndef __FIR_INCLUDE_STRING_H__
#define __FIR_INCLUDE_STRING_H__

#include "Fir/Core/Config.h"
#include "Fir/Core/CharTraits.h"

#if !defined(FIR_SSO_MAX_CHARS)
#   define FIR_SSO_MAX_CHARS 16
#endif

namespace Fir
{
    template<typename CharType>
    class StringBase
    {
    public:
        using Traits = Fir::CharTraits<CharType>;

    public:
        StringBase() = default;
        StringBase(const CharType* string);
        StringBase(const CharType* string ,size_t size);

        StringBase(const StringBase& string);
        StringBase(StringBase&& string);

        ~StringBase();

    public:
        /**
         * Gets the string's capacity.
        */
        size_t Capacity() const;

        /**
         * Gets the C-styled string behind the class.
        */
        const CharType* Data() const;

        /**
         * Gets the string's size.
        */
        size_t Size() const;
        
    private:
        bool _IsLong() const;
        CharType* _Reallocate(size_t newCap);
    
    private:
        static constexpr size_t _bufferSize = FIR_MAX(FIR_SSO_MAX_CHARS / sizeof(CharType), 1);

    private:
        size_t _size = 0;
        size_t _capacity = _bufferSize - 1;

        union
        {
            CharType* ptr;
            CharType buffer[_bufferSize];
        } _data = { 0 };
    };

    using String = Fir::StringBase<char>;
    using Wstring = Fir::StringBase<wchar_t>;
    using U16string = Fir::StringBase<char16_t>;
    using U32string = Fir::StringBase<char32_t>;
}

#endif      // String.h