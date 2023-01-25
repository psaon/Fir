#include "Fir/Core/CharTraits.h"

#include <string.h>

namespace Fir
{
	template<typename CharType>
	size_t CharTraits<CharType>::Length(const CharType* p_str)
	{
		const CharType* end = p_str;
		while (*end++);

		return end - p_str - 1;
	}

	template<typename CharType>
	CharType* CharTraits<CharType>::Copy(CharType* p_dest, const CharType* p_src)
	{
		// Copy the characters.
		while (*p_src)
			*p_dest++ = *p_src++;

		// Copy the null terminator.
		*p_dest = *p_src;
		
		return p_dest;
	}

	template<typename CharType>
	CharType* CharTraits<CharType>::Append(CharType* p_dest, const CharType* p_src)
	{
		// Get the null terminator of the destination string.
		CharType* end = p_dest;
		while (*++end);

		// Copy the string onto the end of it.
		while (*p_src)
			*end++ = *p_src++;

		return p_dest;
	}

	template<typename CharType>
	bool CharTraits<CharType>::Equal(const CharType* p_str1, const CharType* p_str2, size_t p_n)
	{
		return memcmp(p_str1, p_str2, p_n) == 0;
	}

	template<typename CharType>
	CharType* CharTraits<CharType>::Find(CharType* p_str, const CharType p_char)
	{
		CharType* ptr = p_str;
		while (*ptr)
		{
			if (*ptr == p_char)
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