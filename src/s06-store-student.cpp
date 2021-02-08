#include <s22020/Student.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>

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

auto main() -> int {
    std::string first,last,index_no;
    float grade;
    std::cout << "Enter student's data.\nFirst name: ";
    std::cin >> first;
    std::cout << "Last name: ";
    std::cin >> last;
    std::cout << "Index number: ";
    std::cin >> index_no;
    std::cout << "Grade: ";
    std::cin >> grade;
    auto student = s22020::Student{first,last,index_no,grade};
    auto name = std::string{"./student.txt"};
    auto fd = open(name.c_str(), O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    // write
    auto buf = std::string{student.firstname + "\n" + student.lastname + "\n" + student.index_no + "\n" + std::to_string(student.grade_avg) + "\n\n"};
    auto n = write(fd, buf.data(), buf.size());
    if (n == -1) {
        perror("write(2)");
    }
    close(fd);
    return 0;
}
