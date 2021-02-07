#include <iostream>

auto main() -> int {
    int a,b,c;
    // if-else zapisane w formie ternary
    std::cout << "Podaj dwie liczby calkowite: " << std::endl;
    std::cin >> a >> b;
    c = a > b ? a : b;
    std::cout << "Wieksza z liczb " << a << " i " << b << " to " << c << endl;
    // powyzej to to samo co:
    /*
    if (a > b) {
        c = a;
    } else {
        c = b;
    }
    */
    return 0;
}
