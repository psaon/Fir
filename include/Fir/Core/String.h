#ifndef __FIR_INCLUDE_STRING_H__
#define __FIR_INCLUDE_STRING_H__

#include "Fir/Core/Config.h"

#include "Fir/Core/Allocator.h"
#include "Fir/Core/CharTraits.h"

#if !defined(FIR_SSO_MAX_CHARS)
#   define FIR_SSO_MAX_CHARS 16
#endif

FIR_DISABLE_MSVC_WARNING(4245);             // Disable signed/unsigned mismatch warning. (C4245)

namespace Fir
{
    template<typename CharType, typename AllocType>
    class FIR_API StringBase
    {
    private:
        using _Traits = _FIR CharTraits<CharType>;
        using _String = _FIR StringBase<CharType, AllocType>;

    public:
        StringBase() = default;
        StringBase(nullptr_t) = delete;
        StringBase(CharType p_char);
        StringBase(const CharType* p_str);
        StringBase(const CharType* p_str, size_t p_size);

        StringBase(const _String& p_str);
        StringBase(_String&& p_str);

        ~StringBase();

    public:
        CharType& At(const size_t p_index);
        const CharType& At(const size_t p_index) const;
        CharType& Back();
        const CharType& Back() const;
        const CharType* Data() const;
        CharType& Front();
        const CharType& Front() const;
        
        size_t Capacity() const;
        bool Empty() const;
        size_t Length() const;
        _String& Reserve(const size_t p_newCap);
        _String& Shrink();
        size_t Size() const;

        _String& Append(const _String& p_src);
        _String& Clear();

        size_t Find(CharType p_char, size_t p_begin = 0);

    public:
        _String& operator=(const _String& p_str);
        _String& operator=(_String&& p_str);
        
        CharType& operator[](const size_t p_index);
        const CharType& operator[](const size_t p_index) const;

        _String operator+(const _String& p_src);
        _String& operator+=(const _String& p_src);

        bool operator==(const _String& p_str);
        bool operator!=(const _String& p_str);

    public:
        static const size_t NO_POS = -1;

    private:
        // Checks whether the string is allocated on the heap.
        bool _IsLong() const;

    private:
        static constexpr size_t _bufferSize = FIR_MAX(FIR_SSO_MAX_CHARS / sizeof(CharType), 1);

    private:
        union
        {
            CharType* ptr;
            CharType buffer[_bufferSize];
        } _data = { 0 };

        size_t _size = 0;
        size_t _capacity = _bufferSize - 1;

        AllocType _allocator;
    };

    using String = _FIR StringBase<char, _FIR Allocator>;
    using Wstring = _FIR StringBase<wchar_t, _FIR Allocator>;

#if __cplusplus == 202022L
    using U8string = _FIR StringBase<char8_t, _FIR Allocator>;
#endif

    using U16string = _FIR StringBase<char16_t, _FIR Allocator>;
    using U32string = _FIR StringBase<char32_t, _FIR Allocator>;
}

FIR_ENABLE_MSVC_WARNING(4245);

#endif      // String.h