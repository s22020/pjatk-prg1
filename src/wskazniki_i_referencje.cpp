#include <iostream>


auto main() -> int
{
    auto x = 42;
    auto y = &x;
    // wskaznik wskazuje na wartosc pod adresem referencji
    std::cout << *y << " wskaznik\n";
    // referencja wskazuje na adres zmiennej
    std::cout << &x << " referencja\n";


    *y = 43;
    std::cout << x << "\n";
    std::cout << y << "\n";
    auto z = *y;
    std::cout << z
              << "zmienna wskazujaca na zmieniona wartosc (*y) pod adresem "
                 "referencji do x\n";
    std::cout << y
              << "zmienna bedaca wskaznikiem wskazujacym na wartosc pod "
                 "adresem referencji do x\n";
    std::cout << x << "zmienna x\n";
    return 0;
}
