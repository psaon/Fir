#ifndef __FIR_INCLUDE_ERRORLIST_H__
#define __FIR_INCLUDE_ERRORLIST_H__

namespace Fir
{
	enum Error
	{
		ERR_UNKNOWN,
		ERR_FAILED_ALLOC,
	};

    extern const char* ErrorNames[];
}

#endif