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
    class FIR_API StringBase
    {
    private:
        using _Traits = _FIR CharTraits<CharType>;
        using _String = _FIR StringBase<CharType>;

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
        const CharType* Data() const;
        
        size_t Capacity() const;
        _String& Reserve(size_t p_newCap);
        size_t Size() const;

    public:
        _String& operator=(const _String& p_str);
        _String& operator=(_String&& p_str);

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
    };

    using String = _FIR StringBase<char>;
    using Wstring = _FIR StringBase<wchar_t>;

#if __cplusplus == 202022L
    using U8string = _FIR StringBase<char8_t>;
#endif

    using U16string = _FIR StringBase<char16_t>;
    using U32string = _FIR StringBase<char32_t>;
}

#endif      // String.h

// #if !defined(FIR_SSO_MAX_CHARS)
// #   define FIR_SSO_MAX_CHARS 16
// #endif

// FIR_DISABLE_MSVC_WARNING(4245);             // Disable signed/unsigned mismatch warning. (C4245)

// namespace Fir
// {
//     template<typename CharType>
//     class FIR_API StringBase
//     {
//     public:
//         using Traits = Fir::CharTraits<CharType>;

//     public:
//         StringBase() = default;
//         StringBase(const CharType* string);
//         StringBase(const CharType* string, size_t size);
//         StringBase(const CharType& character);

//         StringBase(const StringBase& string);
//         StringBase(StringBase&& string);

//         ~StringBase();

//     public:
//         /**
//          * Appends the specified string to the end.
//         */
//         StringBase<CharType>& Append(const StringBase<CharType>& string);

//         /**
//          * Returns a reference to the first character of the string.
//         */
//         CharType& Begin() const;

//         /**
//          * Gets the string's capacity.
//         */
//         size_t Capacity() const;

//         /**
//          * Gets the C-styled string behind the class.
//         */
//         const CharType* Data() const;

//         /**
//          * Tests whether the string is empty.
//         */
//         bool Empty() const;

//         /**
//          * Returns a reference to the last character of the string.
//         */
//         CharType& End() const;

//         /**
//          * Searches for the specified character.
//          * Returns NO_POS if the specified character is not found.
//         */
//         size_t Find(CharType character);

//         /**
//          * Gets the string's size. Does the same thing as the Size() function.
//         */
//         size_t Length() const;

//         /**
//          * Replaces this string with the specified string.
//         */
//         StringBase<CharType>& Replace(const CharType* string);

//         /**
//          * Reserves the amount of memory specified.
//         */
//         void Reserve(size_t newCap);

//         /**
//          * Reverses the string.
//         */
//         StringBase<CharType>& Reverse();

//         /**
//          * Removes unused capacity.
//         */
//         void Shrink();

//         /**
//          * Gets the string's size.
//         */
//         size_t Size() const;

//     public:
//         /**
//          * Appends the specified string to the end.
//         */
//         StringBase<CharType>& operator+=(const StringBase<CharType>& string);

//         /**
//          * Concatenates two strings.
//         */
//         StringBase<CharType> operator+(const StringBase<CharType>& string);

//         /**
//          * Tests whether two strings are equal.
//         */
//         bool operator==(const StringBase<CharType>& string);
 
//         /**
//          * Tests whether two strings aren't equal.
//         */
//         bool operator!=(const StringBase<CharType>& string);

//         /**
//          * Tests whether the string is empty.
//         */
//         explicit operator bool() const;

//         /**
//          * Accesses the character at the specified index.
//         */
//         CharType& operator[](size_t index) const;

//     public:
//         static const size_t NO_POS = -1;
        
//     private:
//         /**
//          * Returns true if the string is heap allocated, false if it's stack allocated.
//          * It doesn't matter what the size of the string is, just the capacity.
//         */
//         bool _IsLong() const;

//         /**
//          * Reallocates the string to the specified capacity.
//          * If the specified capacity is smaller than _bufferSize, it will allocate on the stack.
//          * If it's larger than _bufferSize, the string will be allocated on the heap.
//         */
//         CharType* _Reallocate(size_t newCap);
    
//     private:
//         static constexpr size_t _bufferSize = FIR_MAX(FIR_SSO_MAX_CHARS / sizeof(CharType), 1);

//     private:
//         size_t _size = 0;
//         size_t _capacity = _bufferSize - 1;

//         union
//         {
//             CharType* ptr;
//             CharType buffer[_bufferSize];
//         } _data = { 0 };
//     };

//     using String = Fir::StringBase<char>;
//     using Wstring = Fir::StringBase<wchar_t>;

// #if __cplusplus == 202022L
//     using U8string = Fir::StringBase<char8_t>;
// #endif

//     using U16string = Fir::StringBase<char16_t>;
//     using U32string = Fir::StringBase<char32_t>;
// }

// FIR_ENABLE_MSVC_WARNING(4245);

// #endif      // String.h