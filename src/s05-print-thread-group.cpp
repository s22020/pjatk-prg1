#include <iostream>
#include <string>
#include <thread>

auto print_stuff(std::string x) -> void {
    std::cout << (x + "\n");
}

auto main() -> int
{
    for (auto i = 0; i < 7; ++i) {
        for (auto j = 1; j < 7; ++j) {
            auto s = std::string{"Hello " + std::to_string(j) + "!"};
            auto p = std::thread{print_stuff, std::move(s)};
            // join powoduje to, ze czekamy az watek sie skonczy i dopiero 
            // wtedy wznawiamy wykonywanie glownego watku programu
            // wiec do glownego watku dolaczamy watki poboczne
            p.join();
        }
    }
    // mutexy sa po to, zeby ochronic jakas sekcje (sekcje krytyczna) programu przed
    // dostepem wielu watkow do niego. w ten sposob tylko jeden
    // watek bedzie mial dostep do tej sekcji
    // referencji nie mozna przekazac bezposrednio do watku tylko przez std::ref
    return 0;

}
