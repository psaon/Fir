#include "Fir/Core/CharTraits.h"

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

	template class CharTraits<char>;
	template class CharTraits<wchar_t>;
	template class CharTraits<char16_t>;
	template class CharTraits<char32_t>;
}