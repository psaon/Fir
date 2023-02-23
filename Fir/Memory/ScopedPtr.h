#ifndef __FIR_MEMORY_SCOPEDPTR_H__
#define __FIR_MEMORY_SCOPEDPTR_H__

#include "Fir/Core/Core.h"

namespace Fir
{
	template<typename Type>
	class ScopedPtr
	{
	public:
		ScopedPtr() = default;
		ScopedPtr(nullptr_t) {  }
		explicit ScopedPtr(Type* p_ptr)
			:_ptr(p_ptr)
		{
		}

		ScopedPtr(const ScopedPtr&) = delete;
		ScopedPtr(ScopedPtr&& p_ptr)
			:_ptr(p_ptr._ptr)
		{
			p_ptr._ptr = nullptr;
		}

		~ScopedPtr()
		{
			delete _ptr;
		}

	public:
		ScopedPtr& operator=(const ScopedPtr&) = delete;
		ScopedPtr& operator=(ScopedPtr&& p_ptr)
		{
			delete _ptr;
			_ptr = p_ptr._ptr;
			p_ptr._ptr = nullptr;
		}

		Type& operator*() const { return *_ptr; }
		Type* operator->() const { return _ptr; }

	private:
		Type* _ptr = nullptr;
	};

	template<typename Type, typename... Args>
	FIR_FORCEINLINE ScopedPtr<Type> MakeScoped(Args&&... args)
	{
		return ScopedPtr<Type>(new Type(static_cast<Args&&>(args)...));
	}
}

#endif		// ScopedPtr.h