#include <string>
#include <iostream>

#include <Fir/Core/String.h>

int main()
{
    Fir::StringBase<char> short_string = "Hello, World!";
    Fir::StringBase<char> long_string = "Hello, World! I am a long string!";
    Fir::StringBase<char> null_string = '\0';

    Fir::StringBase<char16_t> short_16_string = u"Hello";
    Fir::StringBase<char16_t> long_16_string = u"Hello, World!";
    Fir::StringBase<char16_t> null_16_string = u'\0';
}