#include <iostream>

auto print_this(int const* x)
{
    std::cout << *x << " (pointer)\n";
}

auto print_this(int const& x)
{
    std::cout << x << " (reference)\n";
}

auto main() -> int
{
    auto x = 42;
    print_this(&x);
    print_this(x);
}
