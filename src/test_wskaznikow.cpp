#include <iostream>

auto main() -> int
{

    auto x = int{42};

    int* xp = &x;  // potrzebny & żeby dostać wskaźnik
    int& xr = x;    // referencję kompilator stworzy sam

    auto ap = &x;
    auto& ar = x;  // potrzebny znak & ZA TYPEM (nie PRZED ZMIENNĄ), żeby kompilator stworzył referencję, a nie kopię

    *xp = 666;  // przypisanie do wartości za wskaźnikiem (czyli: x == 666, xp == adres zmiennej x)
    xp = 667;   // przypisanie do wskaźnika (czyli: x == 666, xp == 667)
    xr = 668;    // przypisanie do wartości za referencją (czyli: x == 668, xr == adres zmiennej x)
}
