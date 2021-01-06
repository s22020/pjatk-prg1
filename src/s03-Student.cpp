#include <s22020/Student.h>

#include <iostream>
#include <sstream>
#include <string>

// definicja konstruktora
// std::move - zamiast kopiowania przesuwa wartosci i dzieki temu program dziala
// szybciej
s22020::Student::Student(std::string fn, std::string ln, std::string i_no)
        : firstname{std::move(fn)}
        , lastname{std::move(ln)}
        , index_no{std::move(i_no)}
{}

s22020::Student::Student(std::string fn,
                         std::string ln,
                         std::string i_no,
                         float const g)
        : firstname{std::move(fn)}
        , lastname{std::move(ln)}
        , index_no{std::move(i_no)}
        , grade_avg{g}
{}

// definicja funkcji składowej
auto s22020::Student::to_string() const -> std::string
{
    // umożliwia zapis stringu
    auto output = std::ostringstream{};
    output << "Student:\n"
           << firstname << " " << lastname << "\nIndex number:  " << index_no
           << "\nSemester: " << semester << "\nGrade average: " << grade_avg
           << "\n";
    return output.str();
}

auto main() -> int
{
    auto student = s22020::Student{"Zuzanna", "Bernacka", "s22020", 3.5};
    std::cout << student.to_string();
    ++student.grade_avg;
    ++student.grade_avg;
    std::cout << student.grade_avg << "\n";

    return 0;
}
