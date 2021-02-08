#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <mutex>

auto getFromQueue(std::mutex& mtx, std::queue<int>& queue, std::string& x, std::string y) -> void {
    std::lock_guard<std::mutex> lck { mtx };
    std::cout << x << y << " : " << queue.front() << "\n";
    queue.pop();
}

auto main() -> int {
    // kolejka jest domyslnie pusta
    // jesli watek wykryje, ze jest pusta, to watek idzie spac na losowa wartosc miedzy 10 a 100 ms
    // zeby zwolnic mutex i pozwolic kolejce sie zapelnic
    // w main odczytuje napisy z stdin i wkladam na kolejke
    // wiec trzeba tez w funkcji main blokowac sie na mutexie zeby miec gwarancje, ze nie bede pisac
    // i odczytywac z kolejki jednoczesnie (blokowanie i w watkach i w funkcji main)
    // w main petla, ktora bedzie odkladac napisy w kolejke, zakonczenie petli po otrzymaniu 4 pustych napisow
    // zeby kazdy watek dostal pusty napis i mial szanse sie zakonczyc
    // po wyslaniu pustych napisow na kazdym watku zrobic join zeby zapewnic sobie ze sie skoncza
    return 0;
}
