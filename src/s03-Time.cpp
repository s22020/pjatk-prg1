#include <s22020/Time.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

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

auto s22020::Time::convert_to_seconds(Time const& conv_time) const -> int
{
    return (conv_time.hour * 3600 + conv_time.minute * 60 + conv_time.second);
}

auto s22020::Time::convert_from_seconds(unsigned int sec) const -> Time
{
    return Time{(sec / 3600) % 24, (sec / 60) % 60, sec % 60};
}

auto s22020::Time::next_hour() -> void
{
    ++hour;
    if (hour > 23) {
        hour = 0;
    }
}

auto s22020::Time::next_minute() -> void
{
    ++minute;
    if (minute > 59) {
        minute = 0;
        ++hour;
    }
}

auto s22020::Time::next_second() -> void
{
    ++second;
    if (second > 59) {
        second = 0;
        ++minute;
    }
}

auto s22020::Time::to_string() const -> std::string
{
    auto output = std::ostringstream{};
    output << std::setfill('0') << std::setw(2) << hour << ":"
           << std::setfill('0') << std::setw(2) << minute << ":"
           << std::setfill('0') << std::setw(2) << second << "\n";
    return output.str();
}

auto s22020::Time::time_of_day() const -> Time_of_day
{
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

auto s22020::Time::to_string(Time_of_day const time_of_day) -> std::string
{
    switch (time_of_day) {
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

auto s22020::Time::operator+(Time const& time) const -> Time
{
    auto current_seconds = convert_to_seconds(*this);
    auto new_seconds     = convert_to_seconds(time);
    auto all_seconds     = current_seconds + new_seconds;
    auto result          = convert_from_seconds(all_seconds);
    return result;
}


auto s22020::Time::operator-(Time const& time) const -> Time
{
    auto current_seconds = convert_to_seconds(*this);
    auto new_seconds     = convert_to_seconds(time);
    unsigned int all_seconds;
    if (current_seconds < new_seconds) {
        all_seconds = 24 * 3600 + (current_seconds - new_seconds);
    } else {
        all_seconds = current_seconds - new_seconds;
    }
    auto result = convert_from_seconds(all_seconds);
    return result;
}


auto s22020::Time::operator<(Time const& time) const -> bool
{
    auto current_seconds = convert_to_seconds(*this);
    auto new_seconds     = convert_to_seconds(time);
    return (current_seconds < new_seconds);
}

auto s22020::Time::operator>(Time const& time) const -> bool
{
    auto current_seconds = convert_to_seconds(*this);
    auto new_seconds     = convert_to_seconds(time);
    return (current_seconds > new_seconds);
}

auto s22020::Time::operator==(Time const& time) const -> bool
{
    auto current_seconds = convert_to_seconds(*this);
    auto new_seconds     = convert_to_seconds(time);
    return (current_seconds == new_seconds);
}

auto s22020::Time::operator!=(Time const& time) const -> bool
{
    auto current_seconds = convert_to_seconds(*this);
    auto new_seconds     = convert_to_seconds(time);
    return (current_seconds != new_seconds);
}

auto s22020::Time::count_seconds() const -> uint64_t
{
    auto scnds = hour * 3600 + minute * 60 + second;
    return scnds;
}

auto s22020::Time::count_minutes() const -> uint64_t
{
    auto mnts = hour * 60 + minute;
    return mnts;
}

auto s22020::Time::time_to_midnight() const -> Time
{
    auto current_time = convert_to_seconds(*this);
    auto result       = convert_from_seconds(24 * 3600 - current_time);
    return result;
}

auto main() -> int
{
    auto time = s22020::Time{22, 10, 59};
    std::cout << time.to_string();
    time.next_second();
    std::cout << time.to_string();
    time.next_minute();
    std::cout << time.to_string();
    time.next_hour();
    std::cout << time.to_string();
    std::cout << time.to_string(time.time_of_day()) << "\n";
    auto added_time = time.operator+(s22020::Time{23, 0, 1});
    std::cout << added_time.to_string();
    auto substr_time = time.operator-(s22020::Time{1, 0, 1});
    std::cout << substr_time.to_string() << "\n";
    auto other_time = s22020::Time{16, 25, 34};
    std::cout << other_time.to_string() << "\n";
    auto other_add = other_time.operator+(s22020::Time{7, 35, 26});
    std::cout << other_add.to_string() << "\n";
    auto edge       = s22020::Time{0, 0, 0};
    auto edge_minus = edge.operator-(s22020::Time{23, 0, 0});
    std::cout << edge_minus.to_string() << "\n";
    std::cout << "****************************\n";
    auto subtr1    = s22020::Time{10, 10, 0};
    auto subtr2    = s22020::Time{12, 43, 0};
    auto subtr_res = subtr1.operator-(subtr2);
    std::cout << subtr_res.to_string();
    std::cout << subtr1.operator>(subtr2) << "\n";
    auto mid = subtr2.time_to_midnight();
    std::cout << mid.to_string();
    return 0;
}
