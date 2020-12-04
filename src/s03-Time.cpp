#include <s22020/Time.h>
#include <string>
#include <iostream>
#include <sstream>

s22020::Time::Time(unsigned h, unsigned m, unsigned s) 
    : hour{h}, minute{m}, second{s}
{
    if (hour > 23) {
        throw std::logic_error{"Hour must be between 0-23"};
    }

    if (minute > 59) {
        throw std::logic_error{"Minute must be between 0-59"};
    }

    if (second > 59) {
        throw std::logic_error{"Second must be between 0-59"};
    }
}

auto s22020::Time::next_hour() -> void {
    ++hour;
    if (hour > 23) {
        hour = 0;
    }
}

auto s22020::Time::next_minute() -> void {
    ++minute;
    if (minute > 59) {
        minute = 0;
    }
}

auto s22020::Time::next_second() -> void {
    ++second;
    if (second > 59) {
        second = 0;
    }
}

auto s22020::Time::to_string() const -> std::string {
    auto out = std::ostringstream{};
    out << hour << ":" << minute << ":" << second << "\n";
    return out.str();
}

auto s22020::Time::time_of_day() const -> Time_of_day {
    if (hour >= 5 && hour < 12) {
        return Time_of_day::Morning;
    } else if (hour >= 12 && hour < 18) {
        return Time_of_day::Day;
    } else if (hour >= 18 && hour < 23) {
        return Time_of_day::Evening;
    } else {
        return Time_of_day::Night;
    }
}

auto s22020::Time::to_string(Time_of_day const& time_of_day) const -> std::string {
    switch(time_of_day) {
        case Time_of_day::Morning:
            return "Morning";
        case Time_of_day::Day:
            return "Day";
        case Time_of_day::Evening:
            return "Evening";
        case Time_of_day::Night:
            return "Night";
        default:
            throw std::logic_error{"Error"};
        }
}

/*auto s22020::Time::operator+(Time const& time) const -> Time {
    result_hour = hour + time.hour;
    result_minute = minute + time.minute;
    result_second = second + result.second;
    auto result = s22020::Time{result_hour, result_minute, result_second};
    return result;
}*/
/*auto s22020::Time::operator-(Time const&) const -> Time {
auto s22020::Time::operator<(Time const&) const -> Time {
auto s22020::Time::operator>(Time const&) const -> Time {
auto s22020::Time::operator==(Time const&) const -> Time {
auto s22020::Time::operator!=(Time const&) const -> Time {*/

auto main() -> int {
    auto time = s22020::Time{22,59,12};
    std::cout << time.to_string();
    time.next_minute();
    std::cout << time.to_string();
    return 0;
}
