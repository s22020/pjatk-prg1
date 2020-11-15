#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc != 2) {
        throw std::logic_error{"Insufficient amount of arguments"};
    }
    auto bottle_no = std::stoi(argv[1]);
    while (bottle_no > 0) {
        std::cout << bottle_no << " bottles of beer on the wall, " << bottle_no
                  << " bottles of beer.\n";
        std::cout << "Take one down, pass it around, " << bottle_no - 1
                  << " bottles of beer on the wall...\n";
        --bottle_no;
    }
    std::cout
        << "No more bottles of beer on the wall, no more bottles of beer.\n";
    std::cout << "Go to the store and buy some more, " << argv[1]
              << " bottles of beer on the wall...\n";
}
