#include <iostream>
#include <string>
#include <thread>

auto print_stuff(std::string x) -> void
{
    std::cout << x << "\n";
}

auto main() -> int
{
    for (auto i = 0; i < 42; ++i) {
        auto s = std::string{"Hello, "} + std::to_string(i) + "!";
        // pierwszym argumentem jest funkcja, a drugim jej argument
        // nie mam gwarancji czy watki wykonuja sie wszystkie w tym
        // samym momencie czasu
        auto t = std::thread{print_stuff, std::move(s)};
        // detach powoduje, ze nie czekam az watki poboczne sie skoncza
        // tylko dalej wykonuje rownolegle watek glowny programu
        t.detach();
    }

    return 0;
}
