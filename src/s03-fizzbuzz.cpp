#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc != 2) {
        throw std::logic_error{"Invalid amount of arguments."};
    }

    for (auto i = 1; i <= std::stoi(argv[1]); ++i) {
        if ((i % 3 == 0) && (i % 5 == 0)) {
            std::cout << i << " FizzBuzz!\n";
        } else if (i % 3 == 0) {
            std::cout << i << " Fizz!\n";
        } else if (i % 5 == 0) {
            std::cout << i << " Buzz!\n";
        } else {
            std::cout << i << "\n";
        }
    }
    return 0;
}
