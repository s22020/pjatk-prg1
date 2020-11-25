#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc != 2) {
        throw std::logic_error{"Invalid amount of arguments."};
    }

    for (auto i = 1; i <= std::stoi(argv[1]); ++i) {
        std::cout << i;
        if (i % 3 == 0) {
            std::cout << " Fizz";
        }
        if (i % 5 == 0) {
            std::cout << " Buzz";
        }
        std::cout << "\n";
    }
    return 0;
}
