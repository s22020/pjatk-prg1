#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc != 2) {
        throw std::logic_error{"Incorrect amount of arguments."};
    }

    auto const a = std::stoi(argv[1]);
    for (auto i = a; i >= 0; --i) {
        std::cout << i << "...\n";
    }
    return 0;
}
