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

	template class CharTraits<char>;
	template class CharTraits<wchar_t>;
	template class CharTraits<char16_t>;
	template class CharTraits<char32_t>;
}