#include <s22020/Student.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <array>

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
    auto name = std::string{"./build/student.txt"};
    auto fd = open(name.c_str(), O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    std::array<char, 4096> buf { 0 };
    auto const n = read(fd, buf.data(), buf.size());
    if (n == -1) {
        perror("read (2)");
    } else {
        std::cout << std::string{buf.data(), static_cast<size_t>(n)};
    }
    close(fd);

    return 0;
}
