#include <stdio.h>
#include <Fir/Core/String.h>

int main()
{
	Fir::CharTraits<char>::Equal("Hello,", "Hello");
	Fir::CharTraits<char>::Equal("", "Hello");
	Fir::CharTraits<char>::Equal("Hello, World!", "Hello, World!");
	Fir::CharTraits<char>::Equal("Hello,", "Helloasda");
	Fir::CharTraits<char>::Equal("", "");
}