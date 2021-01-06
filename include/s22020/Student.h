#ifndef S22020_STUDENT_H
#define S22020_STUDENT_H

#include <iostream>
#include <sstream>
#include <string>

namespace s22020 {
struct Student {
    std::string const firstname;
    std::string const lastname;
    std::string const index_no;
    unsigned semester{1};
    float grade_avg{2.0};

    // deklaracja konstruktora
    Student(std::string, std::string, std::string);
    Student(std::string, std::string, std::string, float const);

    // deklaracja funkcji składowej
    auto to_string() const -> std::string;
};
}  // namespace s22020
#endif
