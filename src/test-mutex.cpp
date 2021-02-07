#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>

auto print_and_change_stuff(std::mutex& mtx, std::string& x, std::string y) -> void {
    // przez lock guard wykonanie watku zostanie zablokowane do momentu
    // az runtime c++ nie bedzie w stanie przypisac watkowi i zapisac w zmiennej lock guard
    // wlasnosci tego mutexu
    // w momencie jak runtime bedzie w stanie to zrobic, czyli zmienna lock zostanie zablokowana
    // (bedize miala wlasnosc mutexa), to kazdy inny watek, ktory chce uzyskac ta wlasnosc bedzie
    // zablokowany
    std::lock_guard<std::mutex> lck { mtx };
    std::cout << (x + y +"\n");
    x = (x + y);
}

auto main() -> int {
    auto s = std::string{"Hello "};
    // mutexy sa do blokowania sekcji krytycznych przed dostepem do nich
    // kilku watkow na raz
    // zeby zablokowac watek w oczekiwaniu na dostep do sekcji krytycznej
    // uzywa sie std::lock_guard lub std::unique_block
    // do mutexow trzeba uzywac starego stylu deklaracji zmiennych
    /* w zrozumialym wytlumaczeniu mutex - jest to klasa dostarczajaca bezpieczny mechanizm
       do synchronizacji dostepu do danych pomiedzy watkami
       sekcja krytyczna - to wydzielony fragment kodu wykonywany sekwencyjnie w programie wielowatkowym
       (nie moze byc wykonywany rownolegle w takim programie) 
       lock guard - sluzy do zakladania sekcji krytycznej o ograniczonym zasiegu,
       sekcja krytyczna jest zwalniana w momencie gdy zmienna utworzona za pomoca lock_guard przestaje istniec
       czyli w danym watku zakladam lock/blokade na mutual exclusion (powoduje do przeciwdzialanie race condtion
       miedzy innymi) i wtedy tylko ten watek ma dostep do danych 
       mutex nie jest swiadomy, ze chroni konkretna zmienna, to zadaniem programisty jest pamietac o tym
       to troche jakby w fabryce zalozyc klodke na maszyne, ktora w danym momencie czasu musi cos wyprodukowac,
       zeby inne maszyny nie robily jednoczesnie roznych operacji na produkcie (produkt nie jest w domysle tego swiadomy)
    */
    std::mutex s_mtx;
    // teraz dostep do zmiennej jest chroniony mutexem

    //tworze sobie wektor, w ktorym bede przechowywac wskazniki do watkow
    //unique_ptr - jest po to, zeby zajal sie za mnie zwolnieniem pamieci, jest to struktura danych, ktora
    //przechowuje wskaznik i jak wyjdzie unique_ptr poza zakres to uruchomi destruktor na strukturze danych
    //do ktorej przechowuje wskaznik, czyli to tak samo jak zwykla zmienna, ale ta zmienna moze byc zaalokowana
    //dynamicznie. sluzy tez do przenoszenia i kopiowania struktur danych, z ktorymi normalnie nie da sie tak zrobic
    //np std::thread
    auto ts = std::vector<std::unique_ptr<std::thread>>{};
    
    for (auto i = 0; i < 8; ++i) {
        // ponizej po to przekazuje referencje, zeby kazdy watek mial dostep do tej samej zmiennej
        // tak samo mutex, musi byc ten sam i blokowac ta sama zmienna
        auto t = std::make_unique<std::thread>(print_and_change_stuff, std::ref(s_mtx), std::ref(s), std::to_string(i));
        // jak robie detach na watkach to nie mam pewnosci, ze zakoncza sie przed koncem zycia glownego watku,
        // czyli zakonczeniem programu. trzeba wypracowac sobie na to jakis mechanizm, np odpytywanie watkow jakies
        // czy cos w tym stylu
        // w przykladzie ponizej wynosze watek (jego wskaznik) poza oryginalny zakres, zeby moc go sobie 
        // dowolnie przemieszczac, tutaj do wektora (na jego koniec), pozwolic watkom dzialac
        // i wiedzac, ze wektor przechowuje uchwyty do watku po kolei sie joinowac na nim
        // to jest po to, zeby miec pewnosc, ze wszystkie watki zostaly uruchomione zanim program sie zakonczy
        // i zeby mutex zadzialal prawidlowo
        // watki nadal beda w sposob niedeterministyczny dostawac sie do zmiennej, ale bedzie dostep kontrolowany
        // i sekwencyjny (jeden watek na raz)
        ts.push_back(std::move(t));
    }
    for (auto &t : ts) {
        // jako ze jest to wskaznik, to potrzebuje dostac sie do skladowej jego struktury za pomoca strzalki
        t->join();
    }
    return 0;
}
