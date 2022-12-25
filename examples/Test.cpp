#include "Fir/Core/CharTraits.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    FIR_UNREF(argc);
    FIR_UNREF(argv);
    
    size_t len = Fir::CharTraits<char>::Length("Hello, World!");
    printf("Hello World Length: %zd\n", len);
}