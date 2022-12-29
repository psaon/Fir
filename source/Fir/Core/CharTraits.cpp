#include "Fir/Core/CharTraits.h"

#include <string.h>

namespace Fir
{
	template<typename CharType>
	size_t CharTraits<CharType>::Length(const CharType* string)
	{
		const CharType* end = string;
		while (*end++);

		return end - string - 1;
	}

	template<typename CharType>
	CharType* CharTraits<CharType>::Copy(CharType* dest, const CharType* source)
	{
		while (*source)
			*dest++ = *source++;
		
		return dest;
	}

	template<typename CharType>
	CharType* CharTraits<CharType>::Append(CharType* dest, const CharType* source)
	{
		// Get the null terminator of the destination string.
		CharType* end = dest;
		while (*++end);

		// Copy the string onto the end of it.
		while (*source)
			*end++ = *source++;

		return dest;
	}

	template<typename CharType>
	bool CharTraits<CharType>::Compare(const CharType* str1, const CharType* str2, size_t n)
	{
		return memcmp(str1, str2, n) == 0;
	}

	template<typename CharType>
	CharType* CharTraits<CharType>::Find(CharType* string, const CharType character)
	{
		CharType* ptr = string;
		while (*ptr)
		{
			if (*ptr == character)
				return ptr;

			ptr++;
		}
		
		return nullptr;
	}

	template class CharTraits<char>;
	template class CharTraits<wchar_t>;

#	if __cplusplus == 202022L
	template class CharTraits<char8_t>;
#	endif

	template class CharTraits<char16_t>;
	template class CharTraits<char32_t>;
}