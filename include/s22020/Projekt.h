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
};
}  // namespace s22020
#endif
