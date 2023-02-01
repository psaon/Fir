#include <Fir/Memory/Allocator.h>

int main(int argc, char** argv)
{
	FIR_UNREF(argc);    FIR_UNREF(argv);
	
	Fir::Allocator allocator;
	void* mem = allocator.Allocate(20);
}