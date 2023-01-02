#ifndef __FIR_INCLUDE_ARRAY_H__
#define __FIR_INCLUDE_ARRAY_H__

namespace Fir
{
    template<typename Type, size_t ArraySize>
    class Array
    {
    public:
        /**
         * Accesses the first element of the array.
        */
        Type& Begin() const
        {
            return operator[](0);
        }

        /**
         * Retrieves the underlying C-styled array.
        */
        Type* Data() const
        {
            return const_cast<Type*>(_data);
        }

        /**
         * Tests whether the array is empty.
        */
        bool Empty() const
        {
            return Begin() == End();
        }

        /**
         * Accesses the last element of the array.
        */
        Type& End() const
        {
            return operator[](ArraySize - 1);
        }

        /**
         * Gets the size of the array.
        */
        size_t Size() const
        {
            return ArraySize;
        }

    public:
        /**
         * Tests whether the array is not empty.
        */
        explicit operator bool() const { return !Empty(); }

        /**
         * Accesses the element at the specified index.
        */
        Type& operator[](size_t index) const
        {
            return Data()[index];
        }

        /**
         * Tests whether the two arrays are the same.
        */
        template<typename Type2, size_t Size2>
        bool operator==(const Array<Type2, Size2>& arr) const
        {
            if (Size() != Size2)
                return false;

            for (size_t i = 0; i < Size(); ++i)
            {
                if (operator[](i) != arr[i])
                    return false;
            }

            return true;
        }

        /**
         * Tests whether the two arrays are different.
        */
        template<typename Type2, size_t Size2>
        bool operator!=(const Array<Type2, Size2>& arr) const
        {
            return !(*this == arr);
        }

    public:
        Type _data[ArraySize];
    };

    template<typename Type, size_t ArraySize, typename... Types>
    FIR_FORCEINLINE Array<Type, ArraySize> MakeArray(Types&&... elements)
    {
        return { static_cast<Types&&>(elements)... };
    }
}

#endif      // Array.h