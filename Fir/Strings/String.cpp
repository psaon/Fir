#include "Fir/Strings/String.h"

#include <string.h>         // For memcpy()
#include "Fir/Core/Exceptions.h"

namespace Fir
{
//* ==================================================
//* [SECTION]: The Constructors & The Destructor
//* ==================================================

    template<typename CharType, typename AllocType>
    StringBase<CharType, AllocType>::StringBase(CharType p_char)
    {
        if (p_char == _Traits::NullChar)
            return;

        _size = 1;
        _capacity--;

        _data.buffer[0] = p_char;
    }

    template<typename CharType, typename AllocType>
    StringBase<CharType, AllocType>::StringBase(const CharType* p_str)
        :StringBase(p_str, _Traits::Length(p_str))
    {
    }

    template<typename CharType, typename AllocType>
    StringBase<CharType, AllocType>::StringBase(const CharType* p_str, size_t p_size)
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
    StringBase<CharType, AllocType>::StringBase(const _String& p_str)
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
    StringBase<CharType, AllocType>::StringBase(_String&& p_str)
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
    StringBase<CharType, AllocType>::~StringBase()
    {
        if (_IsLong())
            _allocator.Free(_data.ptr);
    }

//* ==================================================
//* [SECTION]: Element Access Member Functions
//* ==================================================

    template<typename CharType, typename AllocType>
    CharType& StringBase<CharType, AllocType>::At(const size_t p_index)
    {
        if (p_index >= Size())
            throw OutOfBoundsException();

        return operator[](p_index);
    }

    template<typename CharType, typename AllocType>
    const CharType& StringBase<CharType, AllocType>::At(const size_t p_index) const
    {
        if (p_index >= Size())
            throw OutOfBoundsException();

        return operator[](p_index);
    }

    template<typename CharType, typename AllocType>
    const CharType* StringBase<CharType, AllocType>::Data() const
    {
        return _IsLong() ? _data.ptr : _data.buffer;
    }

    template<typename CharType, typename AllocType>
    CharType& StringBase<CharType, AllocType>::Front() { return operator[](0); }

    template<typename CharType, typename AllocType>
    const CharType& StringBase<CharType, AllocType>::Front() const { return operator[](0); }

    template<typename CharType, typename AllocType>
    CharType& StringBase<CharType, AllocType>::Back() { return operator[](Size() - 1); }

    template<typename CharType, typename AllocType>
    const CharType& StringBase<CharType, AllocType>::Back() const { return operator[](Size() - 1); }

//* ==================================================
//* [SECTION]: Capacity Member Functions
//* ==================================================

    template<typename CharType, typename AllocType>
    size_t StringBase<CharType, AllocType>::Capacity() const { return _capacity; }

    template<typename CharType, typename AllocType>
    bool StringBase<CharType, AllocType>::Empty() const
    {
        return _size > 0;
    }

    template<typename CharType, typename AllocType>
    size_t StringBase<CharType, AllocType>::Length() const { return _size; }

    template<typename CharType, typename AllocType>
    StringBase<CharType, AllocType>& StringBase<CharType, AllocType>::Reserve(const size_t p_newCap)
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
    StringBase<CharType, AllocType>& StringBase<CharType, AllocType>::Shrink()
    {
        // Return if the capacity is smaller than or equal to size.
        if (Capacity() == Size())
            return *this;
        else if (Capacity() < Size())
            throw _FIR UnknownException();      // If this happens then we have a bug lol

        // If the string is originally not heap allocated, ignore it.
        if (!_IsLong())
            return *this;

        // Check whether the string should be stack or heap allocated.
        if (Size() <= _bufferSize - 1)
        {
            CharType* ptr = _data.ptr;
            _Traits::Copy(_data.buffer, ptr);

            _allocator.Free(ptr);
        }
        else
        {
            CharType* ptr = (CharType*)_allocator.Reallocate(_data.ptr, (Size() + 1) * sizeof(CharType));
            if (!ptr)
                throw _FIR FailedAllocException();

            _data.ptr = ptr;
        }

        _capacity = Size();
        return *this;
    }

    template<typename CharType, typename AllocType>
    size_t StringBase<CharType, AllocType>::Size() const { return _size; }

//* ==================================================
//* [SECTION]: String Operation Member Functions
//* ==================================================

    template<typename CharType, typename AllocType>
    StringBase<CharType, AllocType>& StringBase<CharType, AllocType>::Append(const _String& p_src)
    {
        // Reserve memory for the destination's and the source's string.
        Reserve(Size() + p_src.Size());

        _Traits::Append(&Front(), p_src.Data());
        return *this;
    }

    template<typename CharType, typename AllocType>
    StringBase<CharType, AllocType>& StringBase<CharType, AllocType>::Clear()
    {
        _size = 0;
        operator[](0) = _Traits::NullChar;
        return *this;
    }

//* ==================================================
//* [SECTION]: Search Member Functions
//* ==================================================

    template<typename CharType, typename AllocType>
    size_t StringBase<CharType, AllocType>::Find(CharType p_char, size_t p_begin)
    {
        CharType* ch = _Traits::Find(&Front() + p_begin, p_char);
        if (!ch)
            return NO_POS;

        return ch - &Front();
    }

//* ==================================================
//* [SECTION]: Operator Member Functions
//* ==================================================

    template<typename CharType, typename AllocType>
    StringBase<CharType, AllocType>& StringBase<CharType, AllocType>::operator=(const _String& p_str)
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
    StringBase<CharType, AllocType>& StringBase<CharType, AllocType>::operator=(_String&& p_str)
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
    CharType& StringBase<CharType, AllocType>::operator[](const size_t p_index)
    {
        CharType* buffer = _IsLong() ? _data.ptr : _data.buffer;
        return buffer[p_index];
    }

    template<typename CharType, typename AllocType>
    const CharType& StringBase<CharType, AllocType>::operator[](const size_t p_index) const
    {
        const CharType* buffer = _IsLong() ? _data.ptr : _data.buffer;
        return buffer[p_index];
    }

    template<typename CharType, typename AllocType>
    StringBase<CharType, AllocType> StringBase<CharType, AllocType>::operator+(const _String& p_src)
    {
        _String ret = *this;
        ret.Append(p_src);

        return ret;
    }

    template<typename CharType, typename AllocType>
    StringBase<CharType, AllocType>& StringBase<CharType, AllocType>::operator+=(const _String& p_src)
    {
        return Append(p_src);
    }

    template<typename CharType, typename AllocType>
    bool StringBase<CharType, AllocType>::operator==(const _String& p_str)
    {
        return _Traits::Equal(Data(), p_str.Data());
    }

    template<typename CharType, typename AllocType>
    bool StringBase<CharType, AllocType>::operator!=(const _String& p_str)
    {
        return !(*this == p_str);
    }

//* ==================================================
//* [SECTION]: Private Member Functions
//* ==================================================

    template<typename CharType, typename AllocType>
    bool StringBase<CharType, AllocType>::_IsLong() const
    {
        return _capacity > _bufferSize - 1;
    }

//* ==================================================
//* [SECTION]: Explicit Template Instanciation
//* ==================================================

    template class StringBase<char, Allocator>;
    template class StringBase<wchar_t, Allocator>;

#if __cplusplus == 202022L
    template class StringBase<char8_t, Allocator>;
#endif

    template class StringBase<char16_t, Allocator>;
    template class StringBase<char32_t, Allocator>;


#if defined(FIR_STRING_CUSTOM_ALLOCATOR)
    template class StringBase<char, FIR_STRING_CUSTOM_ALLOCATOR>;
    template class StringBase<wchar_t, FIR_STRING_CUSTOM_ALLOCATOR>;

#   if __cplusplus == 202022L
    template class StringBase<char8_t, FIR_STRING_CUSTOM_ALLOCATOR>;
#   endif

    template class StringBase<char16_t, FIR_STRING_CUSTOM_ALLOCATOR>;
    template class StringBase<char32_t, FIR_STRING_CUSTOM_ALLOCATOR>;
#endif
}