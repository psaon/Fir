#ifndef __FIR_INCLUDE_ARRAY_H__
#define __FIR_INCLUDE_ARRAY_H__

#include "Fir/Core/Typedefs.h"

namespace Fir
{
    template<typename Type, size_t ArrSize>
    class Array
    {
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

    public:
        Type _data[ArrSize];
    };
    
//* ==================================================
//* [SECTION]: Element Access Member Functions
//* ==================================================

    template<typename Type, size_t ArrSize>
    Type& _FIR Array<Type, ArrSize>::At(const size_t p_index)
    {
        if (p_index >= ArrSize)
            return _FIR OutOfBoundsException();

        return operator[](p_index);
    }

    template<typename Type, size_t ArrSize>
    const Type& _FIR Array<Type, ArrSize>::At(const size_t p_index) const
    {
        if (p_index >= ArrSize)
            return _FIR OutOfBoundsException();

        return operator[](p_index);
    }

    template<typename Type, size_t ArrSize>
    Type& _FIR Array<Type, ArrSize>::Back() { return _data[ArrSize - 1]; }

    template<typename Type, size_t ArrSize>
    const Type& _FIR Array<Type, ArrSize>::Back() const { return _data[ArrSize - 1]; }

    template<typename Type, size_t ArrSize>
    Type* _FIR Array<Type, ArrSize>::Data() { return _data; }

    template<typename Type, size_t ArrSize>
    const Type* _FIR Array<Type, ArrSize>::Data() const { return _data; }

    template<typename Type, size_t ArrSize>
    Type& _FIR Array<Type, ArrSize>::Front() { return _data[0]; }

    template<typename Type, size_t ArrSize>
    const Type& _FIR Array<Type, ArrSize>::Front() const { return _data[0]; }

//* ==================================================
//* [SECTION]: Capacity Member Functions
//* ==================================================

    template<typename Type, size_t ArrSize>
    bool _FIR Array<Type, ArrSize>::Empty() const { return ArrSize == 0; }

    template<typename Type, size_t ArrSize>
    size_t _FIR Array<Type, ArrSize>::Size() const { return ArrSize; }

//* ==================================================
//* [SECTION]: Operator Member Functions
//* ==================================================

    template<typename Type, size_t ArrSize>
    Type& _FIR Array<Type, ArrSize>::operator[](const size_t p_index)
    {
        return _data[p_index];
    }

    template<typename Type, size_t ArrSize>
    const Type& _FIR Array<Type, ArrSize>::operator[](const size_t p_index) const
    {
        return _data[p_index];
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