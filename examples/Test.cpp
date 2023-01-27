#include <stdio.h>
#include <Fir/Core/String.h>

int main()
{
    Fir::String string = "Hello, World!";
    string.Find(',', 2);        // found
    string.Find(',', 5);        // found
    string.Find(',', 6);        // not found

    string.Find('H');           // found
    string.Find('!');           // found
    string.Find('h');           // not found
    string.Find('\0');          // not found
}