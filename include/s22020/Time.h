#ifndef S22020_TIME_H
#define S22020_TIME_H

#include <string>
#include <iostream>
#include <sstream>

namespace s22020 {
struct Time {
    unsigned hour{0};
    unsigned minute{0};
    unsigned second{0};
    enum class Time_of_day { Morning, Day, Evening, Night };

    Time(unsigned, unsigned, unsigned);

    auto next_hour() -> void;
    auto next_minute() -> void;
    auto next_second() -> void;
    auto to_string() const -> std::string;
    auto time_of_day() const -> Time_of_day; 
    auto to_string(Time_of_day const&) const -> std::string;
    /*auto operator+ (Time const&) const -> Time;
    auto operator- (Time const&) const -> Time;
    auto operator< (Time const&) const -> bool;
    auto operator> (Time const&) const -> bool;
    auto operator== (Time const&) const -> bool;
    auto operator!= (Time const&) const -> bool;*/
    
};
}
#endif
