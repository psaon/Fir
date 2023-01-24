#ifndef __FIR_INCLUDE_STRINGUTILS_H__
#define __FIR_INCLUDE_STRINGUTILS_H__

#include "Fir/Core/String.h"

namespace Fir
{
    FIR_API Fir::String ToString(bool boolean);
    FIR_API Fir::String ToString(nullptr_t);

    FIR_API Fir::String ToString(void* ptr);
}

#endif      // StringUtils.h