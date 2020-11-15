#include <iostream>
#include <string>

auto enter_password() -> std::string
{
    std::cout << "password: ";
    auto input = std::string{};
    std::getline(std::cin, input);
    return input;
}

auto main(int argc, char* argv[]) -> int
{
    if (argc != 2) {
        throw std::logic_error{"Invalid amount of arguments."};
    }


    while (true) {
        auto password = enter_password();
        if (password == std::string{argv[1]}) {
            std::cout << "ok!\n";
            break;
        }
    }
    return 0;
}
