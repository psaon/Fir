#ifndef __FIR_CONTAINTERS_VECTOR_H__
#define __FIR_CONTAINTERS_VECTOR_H__

#include "Fir/Core/Core.h"
#include "Fir/Core/Exceptions.h"

#include "Fir/Memory/Allocator.h"

namespace Fir
{
    template<typename Type, typename AllocType = _FIR Allocator>
    class Vector
    {
    private:
        using _Vector = _FIR Vector<Type, AllocType>;

    public:
        Vector();

        template<typename... Args>
        Vector(Args&&... p_args)
        {
            static_assert(_FIR IsTypeSame<Args...>::value, "The types are not all the same!");

            Reserve(sizeof...(p_args));
            (Push(p_args), ...);
        }

        Vector(const _Vector& p_vec);
        Vector(_Vector&& p_vec);
        ~Vector();

    public:
        size_t Capacity() const;
        bool Empty() const;
        _Vector& Reserve(const size_t p_newCap);
        _Vector& Shrink();
        size_t Size() const;

        _Vector& Push(const Type& p_val);

    public:
        Type& operator[](const size_t p_index);
        const Type& operator[](const size_t p_index) const;

    private:
        Type* _data = nullptr;

        size_t _size = 0;
        size_t _capacity = 0;

        AllocType _allocator;
    };

//* ==================================================
//* [SECTION]: The Constructors & The Destructor
//* ==================================================

    template<typename Type, typename AllocType>
    Vector<Type, AllocType>::Vector()
    {
        Reserve(1);
        _size = 0;
    }

    template<typename Type, typename AllocType>
    Vector<Type, AllocType>::Vector(const _Vector& p_vec)
    {
        // Reserve
        Reserve(p_vec.Capacity());

        // Copy
        for (size_t i = 0; i < p_vec.Size(); ++i)
            operator[](i) = p_vec[i];
        
        _size = p_vec.Size();
    }

    template<typename Type, typename AllocType>
    Vector<Type, AllocType>::Vector(_Vector&& p_vec)
    {
        _size = p_vec.Size();
        _capacity = p_vec.Capacity();
        _data = p_vec._data;

        p_vec._size = 0;
        p_vec._capacity = 0;
        p_vec._data = nullptr;
    }

    template<typename Type, typename AllocType>
    Vector<Type, AllocType>::~Vector()
    {
        _allocator.Free(_data);
    }

//* ==================================================
//* [SECTION]: Capacity Member Functions
//* ==================================================

    template<typename Type, typename AllocType>
    bool Vector<Type, AllocType>::Empty() const { return _size == 0; }

    template<typename Type, typename AllocType>
    size_t Vector<Type, AllocType>::Size() const { return _size; }

    template<typename Type, typename AllocType>
    size_t Vector<Type, AllocType>::Capacity() const { return _capacity; }

    template<typename Type, typename AllocType>
    typename Vector<Type, AllocType>::_Vector& Vector<Type, AllocType>::Reserve(const size_t p_newCap)
    {
        Type* buffer = (Type*)_allocator.Reallocate(_data, p_newCap * sizeof(Type));
        if (!buffer)
            throw _FIR FailedAllocException();

        _data = buffer;
        _capacity = p_newCap;

        return *this;
    }

    template<typename Type, typename AllocType>
    typename Vector<Type, AllocType>::_Vector& Vector<Type, AllocType>::Shrink()
    {
        if (!Empty())
            return Reserve(Size());

        return *this;
    }

//* ==================================================
//* [SECTION]: Modifier Member Functions
//* ==================================================

    template<typename Type, typename AllocType>
    typename Vector<Type, AllocType>::_Vector& Vector<Type, AllocType>::Push(const Type& p_val)
    {
        // Check whether the vector has enough memory to store the extra value.
        if (Capacity() == Size())
        {
            Reserve(Size() + 1);
        }
        else if (Capacity() < Size())
            // Something must have gone VERY wrong for this exception to be thrown.
            throw _FIR UnknownException();

        _size++;
        _data[_size - 1] = p_val;
    }

//* ==================================================
//* [SECTION]: Operator Member Functions
//* ==================================================

    template<typename Type, typename AllocType>
    Type& Vector<Type, AllocType>::operator[](const size_t p_index) { return _data[p_index]; }

    template<typename Type, typename AllocType>
    const Type& Vector<Type, AllocType>::operator[](const size_t p_index) const { return _data[p_index]; }
}

#endif      // Vector.h