#ifndef S22020_STUDENT_H
#define S22020_STUDENT_H

#include <string>
#include <iostream>
#include <sstream>

namespace s22020 {
struct Student {
    std::string const firstname;
    std::string const lastname;
    std::string const index_no;
    unsigned semester{1};
    float grade_avg{0.0};

    // deklaracja konstruktora
    Student(std::string, std::string, std::string);

    // deklaracja funkcji składowej
    auto to_string() const -> std::string;
};
}
#endif
