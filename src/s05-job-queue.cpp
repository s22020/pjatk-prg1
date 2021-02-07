#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <mutex>

auto getFromQueue(std::mutex& mtx, std::queue<int>& queue, std::string& x, std::string y) -> void {
    std::lock_guard<std::mutex> lck { mtx };
    // biore pierwsza wartosc z poczatku kolejki
    std::cout << x << y <<  " : " << queue.front() << "\n";
    // usuwam wartosc z poczatku kolejki
    queue.pop();
}

auto main() -> int {
    std::queue<int> my_queue;
     for (auto i = 1; i < 5; ++i) {
        my_queue.push(i);
    }
    /* sprawdzenie czy dobrze sie dodaly elementy do kolejki
    std::queue<int> tmp_q = my_queue;
    while (!tmp_q.empty()) {
        auto q_element = tmp_q.front();
        std::cout << q_element <<"\n";
        tmp_q.pop();
    } */
    std::mutex mtx;
    auto x = std::string{"From thread "};
    while (!my_queue.empty()) {
        auto i = 1;
        auto my_thread = std::thread{getFromQueue, std::ref(mtx), std::ref(my_queue), std::ref(x), std::to_string(i)};
        my_thread.join();
        ++i;
    }     
    return 0;
}
