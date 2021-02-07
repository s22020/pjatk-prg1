#include <iostream>
#include <string>

auto main() -> int
{
    auto a = "pizza";
    auto &b = a;
    auto* c = &a;
    auto* d = &b;
    std::cout << "Tworzenie referencji: auto &b = a (" << b << ")" << std::endl;
    std::cout << "Pobieranie adresu zmiennej a: &a (" << &a << ")" << std::endl;
    std::cout << "Pobieranie adresu zmiennej b: &b  (" << &b << ")" << std::endl;
    std::cout << "Wskaznik to zmienna, ktora potrafi przechowywac adres w pamieci jako wartosc\n";
    std::cout << "Wartosc wskaznika do a: auto* c = &a, wyswietlenie c (" << c << ")" << std::endl;
    std::cout << "Wartosc wskaznika do b: auto* d = &b, wyswietlenie d (" << d << ")" << std::endl;
    std::cout << "Nie ma znaczenia czy wskaznik zapiszemy w taki sposob: auto* c = &a;" << std::endl <<
    "Czy w taki: auto * c = &a;" << std::endl << "Czy w taki: auto *c = &a;" << std::endl <<
    "Choc preferowany jest ten pierwszy\n";
    std::cout << "Jest jeszcze operator dereferencji, wtedy zwracana jest wartosc, ktora przechowywana jest pod adresem wskaznika: *c (" << *c << ")" << std::endl;
    std::cout << "Takze * stosowana przy deklaracji zmiennej to wskaznik i przechowuje adres, np. auto* c\n";
    std::cout << "Natomiast * stosowana gdzies indziej niz przy deklaracji to wartosc zmiennej pod adresem wskaznika, np. *c\n";
    std::cout << "Wartosc wskaznika moge zmienic, bo jest to nowa zmienna (kopia), a referencji nie, bo jest to 'odnosnik' do zmiennej" << std::endl;
    std::cout << "Jak zmienie wartosc wskaznika, to zmienie rowniez wartosc zmiennej, na ktora ten wskaznik wskazuje" << std::endl;
    *c = "hamburger";
    std::cout << "Przyklad zmiany wskaznika: *c = \"hamburger\" (" << *c << ")" << std::endl;
    std::cout << "Teraz zmienna a ma wartosc: " << a << std::endl;
    return 0;
}
