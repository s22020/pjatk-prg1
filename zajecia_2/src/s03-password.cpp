#include <iostream>
#include <string>

auto enter_password() -> std::string
{
    std::cout << "password: ";
    auto input = std::string{};
    std::getline(std::cin, input);
    return input;
}

auto main() -> int
{
    while (true) {
        auto password = enter_password();
        if (password == "student") {
            std::cout << "ok!\n";
            break;
        }
    }
    return 0;
}
