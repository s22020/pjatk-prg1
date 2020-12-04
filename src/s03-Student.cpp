#include <s22020/Student.h>
#include <iostream>
#include <string>
#include <sstream>

// definicja konstruktora
s22020::Student::Student(std::string fn, std::string ln, std::string i_no) 
    : firstname{fn}, lastname{ln}, index_no{i_no}
{}

// definicja zmiennej składowej
auto s22020::Student::to_string() const -> std::string {
    // umożliwia zapis stringu
    auto output = std::ostringstream{};
    output << "Student:\n" 
           << firstname << " " << lastname 
           << "\nIndex number:  " 
           << index_no 
           << "\nSemester: " 
           << semester 
           << "\nGrade average: " 
           << grade_avg << "\n";
    return output.str();
} 

auto main() -> int {
    auto student = s22020::Student{"Zuzanna","Bernacka","s22020"};
    std::cout << student.to_string() << "\n";
    ++student.grade_avg;
    std::cout << student.semester << "\n";
    return 0;
}
