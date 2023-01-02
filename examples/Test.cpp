#include <iostream>
#include <Fir/Core/String.h>

#include <Fir/Core/Array.h>

int main()
{
    Fir::Array<Fir::String, 5> array = { "He", "llo", ", ", "Wor", "ld!\n" };
    for (int i = 0; i < 5; ++i)
        std::cout << array[i].Data();

    std::cout << "I think this works?\n";
}

//int FirMain(const List<String>& args, Application& app)
//