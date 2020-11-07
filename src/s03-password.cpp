#include <iostream>
#include <string>


auto main() -> int
{
    while (true) {
        std::cout << "password: ";
        auto input = std::string{};
        std::getline(std::cin, input);
        if (input == "student") {
            std::cout << "ok!";
            break;
        }
    }
    return 0;
}
