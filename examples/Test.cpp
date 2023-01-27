#include <stdio.h>
#include <Fir/Core/String.h>

int main()
{
    Fir::String string = "Hello, ";
	string.Append("World!");

	Fir::String str2 = "abcdefghijklmnopq";
	str2.Append("rstuvwxyz");

	Fir::String str3 = "abcdefghijklmnopq";
	str3.Append("rstuvwxyz0123456789");

	printf("%s, %s, %s\n", string.Data(), str2.Data(), str3.Data());
}