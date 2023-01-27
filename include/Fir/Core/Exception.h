#ifndef __FIR_INCLUDE_EXCEPTION_H__
#define __FIR_INCLUDE_EXCEPTION_H__

namespace Fir
{
    class Exception
    {
    public:
        Exception() = default;

        Exception(const Exception&) = default;
        Exception(Exception&&) = default;
        virtual ~Exception() = default;

        virtual const char* What() const noexcept = 0;
    };
}

#define _FIR_DEFINE_EXCEPTION(name, msg) \
    class name : public ::Fir::Exception { public: virtual const char* What() const noexcept override { return msg; } }

namespace Fir
{
    _FIR_DEFINE_EXCEPTION(FailedAllocException, "Failed to allocate memory.");
    _FIR_DEFINE_EXCEPTION(OutOfBoundsException, "Out of bounds.");
    _FIR_DEFINE_EXCEPTION(UnknownException, "Unknown error occured.");
}

#undef _FIR_DEFINE_EXCEPTION

#endif        // Exception.h