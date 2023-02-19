#ifndef __FIR_INCLUDE_ARRAY_H__
#define __FIR_INCLUDE_ARRAY_H__

#include "Fir/Core/Core.h"

namespace Fir
{
    template<typename Type, size_t ArrSize>
    class Array
    {
    private:
        using _Array = _FIR Array<Type, ArrSize>;

    public:
        Type& At(const size_t p_index);
        const Type& At(const size_t p_index) const;
        Type& Back();
        const Type& Back() const;
        Type* Data();
        const Type* Data() const;
        Type& Front();
        const Type& Front() const;

        bool Empty() const;
        size_t Size() const;

    public:
        Type& operator[](const size_t p_index);
        const Type& operator[](const size_t p_index) const;

        bool operator==(const _Array& p_arr);
        bool operator!=(const _Array& p_arr);

    public:
        Type _data[ArrSize];
    };
    
//* ==================================================
//* [SECTION]: Element Access Member Functions
//* ==================================================

    template<typename Type, size_t ArrSize>
    Type& Array<Type, ArrSize>::At(const size_t p_index)
    {
        if (p_index >= ArrSize)
            return _FIR OutOfBoundsException();

        return operator[](p_index);
    }

    template<typename Type, size_t ArrSize>
    const Type& Array<Type, ArrSize>::At(const size_t p_index) const
    {
        if (p_index >= ArrSize)
            return _FIR OutOfBoundsException();

        return operator[](p_index);
    }

    template<typename Type, size_t ArrSize>
    Type& Array<Type, ArrSize>::Back() { return _data[ArrSize - 1]; }

    template<typename Type, size_t ArrSize>
    const Type& Array<Type, ArrSize>::Back() const { return _data[ArrSize - 1]; }

    template<typename Type, size_t ArrSize>
    Type* Array<Type, ArrSize>::Data() { return _data; }

    template<typename Type, size_t ArrSize>
    const Type* Array<Type, ArrSize>::Data() const { return _data; }

    template<typename Type, size_t ArrSize>
    Type& Array<Type, ArrSize>::Front() { return _data[0]; }

    template<typename Type, size_t ArrSize>
    const Type& Array<Type, ArrSize>::Front() const { return _data[0]; }

//* ==================================================
//* [SECTION]: Capacity Member Functions
//* ==================================================

    template<typename Type, size_t ArrSize>
    bool Array<Type, ArrSize>::Empty() const { return ArrSize == 0; }

    template<typename Type, size_t ArrSize>
    size_t Array<Type, ArrSize>::Size() const { return ArrSize; }

//* ==================================================
//* [SECTION]: Operator Member Functions
//* ==================================================

    template<typename Type, size_t ArrSize>
    Type& Array<Type, ArrSize>::operator[](const size_t p_index)
    {
        return _data[p_index];
    }

    template<typename Type, size_t ArrSize>
    const Type& Array<Type, ArrSize>::operator[](const size_t p_index) const
    {
        return _data[p_index];
    }

    template<typename Type, size_t ArrSize>
    bool Array<Type, ArrSize>::operator==(const _Array& p_arr)
    {
        for (size_t i = 0; i < Size(); ++i)
        {
            if (operator[](i) != p_arr[i])
                return false;
        }

        return true;
    }

    template<typename Type, size_t ArrSize>
    bool Array<Type, ArrSize>::operator!=(const _Array& p_arr)
    {
        return !(*this == p_arr);
    }

//* ==================================================
//* [SECTION]: Factory Function
//* ==================================================

    template<typename Type, typename... Args>
    FIR_FORCEINLINE _FIR Array<Type, sizeof(Args)...> MakeArray(Args&&... p_args)
    {
        return _FIR Array<Type, sizeof(Args)...>{ static_cast<Type&&>(p_args)... };
    }
}

#endif      // Array.h