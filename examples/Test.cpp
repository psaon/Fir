#include "../Fir/Strings/String.h"
#include "../Fir/Containers/Array.h"

#include "../Fir/Memory/ScopedPtr.h"

int main()
{ 
	Fir::String string = "Hello, World!";
	Fir::Array<int, 3> arr = { 0, 1, 2 };
	arr = { 2, 3, 5 };

	Fir::ScopedPtr<int> ptr = Fir::MakeScoped<int>(5);
}