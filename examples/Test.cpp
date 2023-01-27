#include <stdio.h>
#include <Fir/Core/Array.h>
#include <Fir/Core/String.h>

int main()
{
    Fir::Array<size_t, 3> arr = { 0, 1, 2 };
	arr.Size();
}