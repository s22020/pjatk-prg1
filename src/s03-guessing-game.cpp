#include <iostream>
#include <random>
#include <string>

auto guess_number() -> int
{
    std::cout << "guess: ";
    auto input = std::string{};
    std::getline(std::cin, input);
    return std::stoi(input);
}

auto main() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> rnd(1, 100);
    auto const pc_number = rnd(rd);
    while (true) {
        auto const user_number = guess_number();
        if (user_number < pc_number) {
            std::cout << "number too small!\n";
        } else if (user_number > pc_number) {
            std::cout << "number too big!\n";
        } else {
            std::cout << "just right!\n";
            break;
        }
    }
    return 0;
}
