#ifndef S22020_PROJEKT_H
#define S22020_PROJEKT_H

#include <iostream>
#include <sstream>
#include <string>

namespace s22020 {
struct Entry {
    std::string title{};
    std::string username{};
    std::string password{};
    std::string url{};
    
    Entry(std::string, std::string, std::string, std::string);
    // generate random number in given ASCII range
    auto generate_ascii_dec(unsigned, unsigned) -> char;
    
};
}  // namespace s22020
#endif
