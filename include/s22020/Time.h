#ifndef S22020_TIME_H
#define S22020_TIME_H

#include <iostream>
#include <sstream>
#include <string>

namespace s22020 {
struct Time {
    unsigned hour{0};
    unsigned minute{0};
    unsigned second{0};
    enum class Time_of_day { Morning, Day, Evening, Night };
    
    Time(unsigned, unsigned, unsigned);

    auto convert_to_seconds(Time const&) const -> int;
    auto convert_from_seconds(unsigned int) const -> Time;
    auto next_hour() -> void;
    auto next_minute() -> void;
    auto next_second() -> void;
    auto to_string() const -> std::string;
    auto time_of_day() const -> Time_of_day;
    static auto to_string(Time_of_day const) -> std::string;
    auto operator+(Time const&) const -> Time;
    auto operator-(Time const&) const -> Time;
    auto operator<(Time const&) const -> bool;
    auto operator>(Time const&) const -> bool;
    auto operator==(Time const&) const -> bool;
    auto operator!=(Time const&) const -> bool;
    auto count_seconds() const -> uint64_t;
    auto count_minutes() const -> uint64_t;
    auto time_to_midnight() const -> Time;
};
}  // namespace s22020
#endif
