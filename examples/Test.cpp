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

	
}