#include "Fir/Core/String.h"
#include <string.h>         // For memcpy()

namespace Fir
{
//* ==================================================
//* [SECTION]: The Constructors & The Destructor
//* ==================================================

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType>::StringBase(CharType p_char)
    {
        if (p_char == _Traits::NULL_CHAR)
            return;

        _size = 1;
        _capacity--;

        _data.buffer[0] = p_char;
    }

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType>::StringBase(const CharType* p_str)
        :StringBase(p_str, _Traits::Length(p_str))
    {
    }

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType>::StringBase(const CharType* p_str, size_t p_size)
    {
        CharType* buffer = _data.buffer;

        // Checks whether the string should be allocated on the heap.
        if (p_size > _bufferSize - 1)
        {
            buffer = _data.ptr = (CharType*)_allocator.Allocate((p_size + 1) * sizeof(CharType));
            if (!buffer) throw _FIR FailedAllocException();

            _capacity = p_size;
        }

        // Copy the string to the buffer.
        _Traits::Copy(buffer, p_str);
        _size = p_size;
    }

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType>::StringBase(const _String& p_str)
    {
        CharType* buffer = _data.buffer;

        // Check whether the string should be allocated on the heap.
        if (p_str._IsLong())
        {
            buffer = _data.ptr = (CharType*)_allocator.Allocate(p_str.Capacity() * sizeof(CharType));
            if (!buffer)
                throw _FIR FailedAllocException();
        }
        
        // Copy the string to the buffer.
        _Traits::Copy(buffer, p_str.Data());

        _capacity = p_str.Capacity();
        _size = p_str.Size();
    }

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType>::StringBase(_String&& p_str)
    {
        // Copy
        _size = p_str.Size();
        _capacity = p_str.Capacity();

        if (p_str._IsLong())
            _data.ptr = p_str._data.ptr;
        else
            _Traits::Copy(_data.buffer, p_str._data.buffer);

        // Set
        p_str._size = 0;
        p_str._capacity = 0;
        p_str._data.ptr = nullptr;
    }

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType>::~StringBase()
    {
        if (_IsLong())
            _allocator.Free(_data.ptr);
    }

//* ==================================================
//* [SECTION]: Element Access Member Functions
//* ==================================================

    template<typename CharType, typename AllocType>
    CharType& _FIR StringBase<CharType, AllocType>::At(const size_t p_index)
    {
        if (p_index >= Size())
            throw _FIR OutOfBoundsException();

        return operator[](p_index);
    }

    template<typename CharType, typename AllocType>
    const CharType& _FIR StringBase<CharType, AllocType>::At(const size_t p_index) const
    {
        if (p_index >= Size())
            throw _FIR OutOfBoundsException();

        return operator[](p_index);
    }

    template<typename CharType, typename AllocType>
    const CharType* _FIR StringBase<CharType, AllocType>::Data() const
    {
        return _IsLong() ? _data.ptr : _data.buffer;
    }

    template<typename CharType, typename AllocType>
    CharType& _FIR StringBase<CharType, AllocType>::Front() { return operator[](0); }

    template<typename CharType, typename AllocType>
    const CharType& _FIR StringBase<CharType, AllocType>::Front() const { return operator[](0); }

    template<typename CharType, typename AllocType>
    CharType& _FIR StringBase<CharType, AllocType>::Back() { return operator[](Size() - 1); }

    template<typename CharType, typename AllocType>
    const CharType& _FIR StringBase<CharType, AllocType>::Back() const { return operator[](Size() - 1); }

//* ==================================================
//* [SECTION]: Capacity Member Functions
//* ==================================================

    template<typename CharType, typename AllocType>
    size_t _FIR StringBase<CharType, AllocType>::Capacity() const { return _capacity; }

    template<typename CharType, typename AllocType>
    bool _FIR StringBase<CharType, AllocType>::Empty() const
    {
        return _size > 0;
    }

    template<typename CharType, typename AllocType>
    size_t _FIR StringBase<CharType, AllocType>::Length() const { return _size; }

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType>& _FIR StringBase<CharType, AllocType>::Reserve(const size_t p_newCap)
    {
        // Return if the new capacity is smaller than the original capacity.
        if (p_newCap <= _capacity)
            return *this;

        size_t bytesAlloc = (p_newCap + 1) * sizeof(CharType);

        if (_IsLong())
        {
            // Reallocate the buffer.
            CharType* buffer = (CharType*)_allocator.Reallocate(_data.ptr, bytesAlloc);
            if (!buffer)
                throw _FIR FailedAllocException();

            _data.ptr = buffer;
        }
        else
        {
            // Allocate buffer on the heap.
            CharType* buffer = (CharType*)_allocator.Allocate(bytesAlloc);
            if (!buffer)
                throw _FIR FailedAllocException();

            // Copy the contents of the stack allocated buffer to
            // the heap allocated buffer.
            _Traits::Copy(buffer, _data.buffer);
            _data.ptr = buffer;
        }
        
        // Set capacity to the new capacity.
        _capacity = p_newCap;
        return *this;
    }

    template<typename CharType, typename AllocType>
    size_t _FIR StringBase<CharType, AllocType>::Size() const { return _size; }

//* ==================================================
//* [SECTION]: String Operation Member Functions
//* ==================================================

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType>& _FIR StringBase<CharType, AllocType>::Append(const _String& p_src)
    {
        // Reserve memory for the destination's and the source's string.
        Reserve(Size() + p_src.Size());

        _Traits::Append(&Front(), p_src.Data());
        return *this;
    }

//* ==================================================
//* [SECTION]: Operator Member Functions
//* ==================================================

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType>& _FIR StringBase<CharType, AllocType>::operator=(const _String& p_str)
    {
        // Free the heap allocated buffer.
        if (_IsLong())
            _allocator.Free(_data.ptr);

        // Check whether the string should be allocated on the heap.
        CharType* buffer = _data.buffer;
        if (p_str._IsLong())
        {
            buffer = _data.ptr = (CharType*)_allocator.Allocate((p_str.Capacity() + 1) * sizeof(CharType));
            if (!buffer)
                throw _FIR FailedAllocException();
        }

        // Copy the string to the buffer.
        _Traits::Copy(buffer, p_str.Data());

        _size = p_str.Size();
        _capacity = p_str.Capacity();

        return *this;
    }

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType>& _FIR StringBase<CharType, AllocType>::operator=(_String&& p_str)
    {
        // Free
        if (_IsLong())
            _allocator.Free(_data.ptr);

        // Copy
        _size = p_str.Size();
        _capacity = p_str.Capacity();

        if (p_str._IsLong())
            _data.ptr = p_str._data.ptr;
        else
            _Traits::Copy(_data.buffer, p_str._data.buffer);

        // Set
        p_str._size = 0;
        p_str._capacity = 0;
        p_str._data.ptr = nullptr;

        return *this;
    }

    template<typename CharType, typename AllocType>
    CharType& _FIR StringBase<CharType, AllocType>::operator[](const size_t p_index)
    {
        CharType* buffer = _IsLong() ? _data.ptr : _data.buffer;
        return buffer[p_index];
    }

    template<typename CharType, typename AllocType>
    const CharType& _FIR StringBase<CharType, AllocType>::operator[](const size_t p_index) const
    {
        const CharType* buffer = _IsLong() ? _data.ptr : _data.buffer;
        return buffer[p_index];
    }

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType> _FIR StringBase<CharType, AllocType>::operator+(const _String& p_src)
    {
        Fir::String ret = *this;
        ret.Append(p_src);

        return ret;
    }

    template<typename CharType, typename AllocType>
    _FIR StringBase<CharType, AllocType>& _FIR StringBase<CharType, AllocType>::operator+=(const _String& p_src)
    {
        return Append(p_src);
    }

//* ==================================================
//* [SECTION]: Private Member Functions
//* ==================================================

    template<typename CharType, typename AllocType>
    bool _FIR StringBase<CharType, AllocType>::_IsLong() const
    {
        return _capacity > _bufferSize - 1;
    }

    template class _FIR StringBase<char, _FIR Allocator>;
    template class _FIR StringBase<wchar_t, _FIR Allocator>;

#if __cplusplus == 202022L
    template class _FIR StringBase<char8_t, _FIR Allocator>;
#endif

    template class _FIR StringBase<char16_t, _FIR Allocator>;
    template class _FIR StringBase<char32_t, _FIR Allocator>;


#if defined(FIR_STRING_CUSTOM_ALLOCATOR)
    template class _FIR StringBase<char, FIR_STRING_CUSTOM_ALLOCATOR>;
    template class _FIR StringBase<wchar_t, FIR_STRING_CUSTOM_ALLOCATOR>;

#   if __cplusplus == 202022L
    template class _FIR StringBase<char8_t, FIR_STRING_CUSTOM_ALLOCATOR>;
#   endif

    template class _FIR StringBase<char16_t, FIR_STRING_CUSTOM_ALLOCATOR>;
    template class _FIR StringBase<char32_t, FIR_STRING_CUSTOM_ALLOCATOR>;
#endif
}

// #include <string.h>
// #include <stdlib.h>

// namespace Fir
// {
// //* ==================================================
// //* [SECTION]: Constructor & Destructor
// //* ==================================================

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType>::StringBase(const CharType* string)
//         :StringBase(string, Traits::Length(string))
//     {
//     }

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType>::StringBase(const CharType* string, size_t size)
//     {
//         CharType* buffer;
//         _size = size;

//         if (_size < _bufferSize)
//         {
//             buffer = _data.buffer;
//             _capacity = _bufferSize - 1;
//         }
//         else
//         {
//             buffer = _data.ptr = (CharType*)calloc(_size + 1, sizeof(CharType));
//             if (!_data.ptr)
//                 throw FailedAllocException();

//             _capacity = _size;
//         }

//         Traits::Copy(buffer, string);
//     }

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType>::StringBase(const CharType& character)
//     {
//         _size = 1;
//         _capacity = _bufferSize - 1;
//         _data.buffer[0] = character;
//     }

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType>::StringBase(const StringBase& string)
//         :StringBase(string.Data(), string._size)
//     {
//     }

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType>::StringBase(StringBase&& string)
//     {
//         // Copy
//         _size = string._size;
//         _capacity = string._capacity;

//         memcpy(&_data, &string._data, sizeof(_data));

//         // Set to 0
//         string._size = 0;
//         string._capacity = 0;
//         memset(&string._data, 0, sizeof(_data));
//     }

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType>::~StringBase()
//     {
//         if (_IsLong())
//             free(_data.ptr);
//     }

// //* ==================================================
// //* [SECTION]: Public Member Functions
// //* ==================================================

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType>& StringBase<CharType, AllocType>::Append(const StringBase<CharType, AllocType>& string)
//     {
//         size_t newSize = Size() + string.Size();
//         if (newSize > Capacity())
//             _Reallocate(newSize);

//         Traits::Append(_IsLong() ? _data.ptr : _data.buffer, string.Data());
//         _size = newSize;
        
//         return *this;
//     }

//     template<typename CharType, typename AllocType>
//     CharType& StringBase<CharType, AllocType>::Begin() const
//     {
//         return operator[](0);
//     }

//     template<typename CharType, typename AllocType>
//     size_t StringBase<CharType, AllocType>::Capacity() const
//     {
//         return _capacity;
//     }

//     template<typename CharType, typename AllocType>
//     const CharType* StringBase<CharType, AllocType>::Data() const
//     {
//         return _IsLong() ? _data.ptr : _data.buffer;
//     }

//     template<typename CharType, typename AllocType>
//     bool StringBase<CharType, AllocType>::Empty() const
//     {
//         return Size() == 0;
//     }

//     template<typename CharType, typename AllocType>
//     CharType& StringBase<CharType, AllocType>::End() const
//     {
//         return operator[](Size() - 1);
//     }

//     template<typename CharType, typename AllocType>
//     size_t StringBase<CharType, AllocType>::Find(CharType character)
//     {
//         CharType* ptr = Traits::Find(&Begin(), character);
//         return ptr ? ptr - Data() : NO_POS;
//     }

//     template<typename CharType, typename AllocType>
//     size_t StringBase<CharType, AllocType>::Length() const
//     {
//         return _size;
//     }

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType>& StringBase<CharType, AllocType>::Replace(const CharType* string)
//     {
//         size_t len = Traits::Length(string);
//         CharType* ptr = &Begin();

//         if (len > Capacity())
//             ptr = _Reallocate(len);

//         Traits::Copy(ptr, string);
//         _size = len;

//         return *this;
//     }

//     template<typename CharType, typename AllocType>
//     void StringBase<CharType, AllocType>::Reserve(size_t newCap)
//     {
//         _Reallocate(newCap);
//     }

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType>& StringBase<CharType, AllocType>::Reverse()
//     {
//         size_t i, j;
//         CharType c;

//         for (i = 0, j = Size() - 1; i < j; ++i, --j)
//         {
//             c = operator[](i);
//             operator[](i) = operator[](j);
//             operator[](j) = c;
//         }

//         return *this;
//     }

//     template<typename CharType, typename AllocType>
//     void StringBase<CharType, AllocType>::Shrink()
//     {
//         if (_IsLong())
//             _Reallocate(Size());
//     }

//     template<typename CharType, typename AllocType>
//     size_t StringBase<CharType, AllocType>::Size() const
//     {
//         return _size;
//     }

// //* ==================================================
// //* [SECTION]: Operators
// //* ==================================================

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType>& StringBase<CharType, AllocType>::operator+=(const StringBase& string)
//     {
//         return Append(string);
//     }

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType> StringBase<CharType, AllocType>::operator+(const StringBase<CharType, AllocType>& string)
//     {
//         auto ret = *this;
//         ret.Append(string);

//         return ret;
//     }

//     template<typename CharType, typename AllocType>
//     bool StringBase<CharType, AllocType>::operator==(const StringBase<CharType, AllocType>& string)
//     {
//         return (Size() == string.Size()) && Traits::Compare(Data(), string.Data(), Size());
//     }

//     template<typename CharType, typename AllocType>
//     bool StringBase<CharType, AllocType>::operator!=(const StringBase<CharType, AllocType>& string)
//     {
//         return !(*this == string);
//     }

//     template<typename CharType, typename AllocType>
//     StringBase<CharType, AllocType>::operator bool() const
//     {
//         return Size() != 0;
//     }

//     template<typename CharType, typename AllocType>
//     CharType& StringBase<CharType, AllocType>::operator[](size_t index) const
//     {
//         return const_cast<CharType&>(Data()[index]);
//     }

// //* ==================================================
// //* [SECTION]: Private Member Functions
// //* ==================================================

//     template<typename CharType, typename AllocType>
//     bool StringBase<CharType, AllocType>::_IsLong() const
//     {
//         return _capacity > _bufferSize;
//     }

//     template<typename CharType, typename AllocType>
//     CharType* StringBase<CharType, AllocType>::_Reallocate(size_t newCap)
//     {
//         // Stack allocated strings can fit 15 bytes.
//         // Any bigger strings will be allocated on the heap.

//         if (newCap < _bufferSize)
//         {
//             if (_IsLong())
//             {
//                 CharType* heapBuffer = _data.ptr;
//                 memcpy(_data.buffer, heapBuffer, sizeof(CharType) * _bufferSize);   // Can cause buffer overflows if using Traits::Copy
//                 free(heapBuffer);

//                 _capacity = _bufferSize - 1;
//             }

//             return _data.buffer;
//         }
//         else
//         {
//             if (_IsLong())
//             {
//                 CharType* newBlock = (CharType*)realloc(_data.ptr, (newCap + 1) * sizeof(CharType));
//                 if (newBlock)
//                     _data.ptr = newBlock;
//                 else
//                 {
//                     free(_data.ptr);
//                     throw FailedAllocException();
//                 }
//             }
//             else
//             {
//                 CharType* heapBuffer = (CharType*)calloc(newCap + 1, sizeof(CharType));
//                 if (!heapBuffer)
//                     throw FailedAllocException();

//                 Traits::Copy(heapBuffer, _data.buffer);
//                 _data.ptr = heapBuffer;
//             }

//             _capacity = newCap;
//             return _data.ptr;
//         }
//     }

// //* ==================================================
// //* [SECTION]: Explicit Template Instantiation
// //* ==================================================
//     template class StringBase<char>;
//     template class StringBase<wchar_t>;

// #if __cplusplus == 202022L
//     template class StringBase<char8_t>;
// #endif

//     template class StringBase<char16_t>;
//     template class StringBase<char32_t>;
// }