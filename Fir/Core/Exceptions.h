#ifndef __FIR_CORE_EXCEPTIONS_H__
#define __FIR_CORE_EXCEPTIONS_H__

#include "Fir/Core/Macros.h"

namespace Fir
{
    class Exception
    {
    public:
        Exception() = default;

        Exception(const Exception&) = default;
        Exception(Exception&&) = default;
        virtual ~Exception() = default;

    public:
        virtual const char* What() const noexcept;
    };

#define _FIR_DEFINE_EXCEPTION(name, msg) \
    class name : public _FIR Exception { virtual const char* What() const noexcept override { return msg; } }

    _FIR_DEFINE_EXCEPTION(FailedAllocException, "Failed to allocate memory.");
}

#undef _FIR_DEFINE_EXCEPTION

#endif      // Exception.h