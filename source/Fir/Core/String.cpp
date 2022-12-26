#include "Fir/Core/String.h"

#include <string.h>
#include <stdlib.h>

namespace Fir
{
//* ==================================================
//* [SECTION]: Constructor & Destructor
//* ==================================================

    template<typename CharType>
    StringBase<CharType>::StringBase(const CharType* string)
        :StringBase(string, Traits::Length(string))
    {
    }

    template<typename CharType>
    StringBase<CharType>::StringBase(const CharType* string, size_t size)
    {
        CharType* buffer;
        _size = size;

        if (_size < _bufferSize)
        {
            buffer = _data.buffer;
            _capacity = _bufferSize - 1;
        }
        else
        {
            buffer = _data.ptr = (CharType*)calloc(_size + 1, sizeof(CharType));
            if (!_data.ptr)
                throw 110;

            _capacity = _size;
        }

        Traits::Copy(buffer, string);
    }

    template<typename CharType>
    StringBase<CharType>::StringBase(const StringBase& string)
        :StringBase(string.Data(), string._size)
    {
    }

    template<typename CharType>
    StringBase<CharType>::StringBase(StringBase&& string)
    {
        // Copy
        _size = string._size;
        _capacity = string._capacity;

        memcpy(&_data, &string._data, sizeof(_data));

        // Set to 0
        string._size = 0;
        string._capacity = 0;
        memset(&string._data, 0, sizeof(_data));
    }

    template<typename CharType>
    StringBase<CharType>::~StringBase()
    {
        if (_IsLong())
            free(_data.ptr);
    }

//* ==================================================
//* [SECTION]: Public Member Functions
//* ==================================================

    template<typename CharType>
    size_t StringBase<CharType>::Capacity() const
    {
        return _capacity;
    }

    template<typename CharType>
    const CharType* StringBase<CharType>::Data() const
    {
        return _IsLong() ? _data.ptr : _data.buffer;
    }

    template<typename CharType>
    size_t StringBase<CharType>::Size() const
    {
        return _size;
    }

//* ==================================================
//* [SECTION]: Private Member Functions
//* ==================================================

    template<typename CharType>
    bool StringBase<CharType>::_IsLong() const
    {
        return _capacity > _bufferSize;
    }

    template<typename CharType>
    CharType* StringBase<CharType>::_Reallocate(size_t newCap)
    {
        // Stack allocated strings can fit 15 bytes.
        // Any bigger strings will be allocated on the heap.

        if (newCap < _bufferSize)
        {
            if (_IsLong())
            {
                CharType* heapBuffer = _data.ptr;
                Traits::Copy(_data.buffer, heapBuffer);
                free(heapBuffer);

                _capacity = _bufferSize - 1;
            }

            return _data.buffer;
        }
        else
        {
            if (_IsLong())
            {
                _data.ptr = (CharType*)realloc(_data.ptr, (newCap + 1) * sizeof(CharType));
                if (!_data.ptr)
                    throw 110;
            }
            else
            {
                CharType* heapBuffer = (CharType*)calloc(newCap + 1, sizeof(CharType));
                if (!heapBuffer)
                    throw 110;

                Traits::Copy(heapBuffer, _data.buffer);
                _data.ptr = heapBuffer;
            }

            _capacity = newCap;
            return _data.ptr;
        }
    }

//* ==================================================
//* [SECTION]: Explicit Template Instantiation
//* ==================================================
    template class StringBase<char>;
    template class StringBase<wchar_t>;
    template class StringBase<char16_t>;
    template class StringBase<char32_t>;
}