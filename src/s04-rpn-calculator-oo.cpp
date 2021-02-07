/*
 * A reverse-polish notation calculator.
 */
#include <s22020/RPN_calculator.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>


auto pop_top(std::stack<double>& stack) -> double
{
    if (stack.empty()) {
        throw std::logic_error{"empty stack"};
    }
    auto element = std::move(stack.top());
    stack.pop();
    return element;
}

s22020::rpn_calculator::Element::~Element()
{}

s22020::rpn_calculator::Literal::Literal(double const v) : value{v}
{}

auto s22020::rpn_calculator::Literal::evaluate(stack_type& stack) const -> void {
    stack.push(value);
}

auto s22020::rpn_calculator::Print::evaluate(stack_type& stack) const -> void {
    std::cout << stack.top() << "\n";
}


auto s22020::rpn_calculator::Addition::evaluate(stack_type& stack) const -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for +"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a + b);
}

auto s22020::rpn_calculator::Subtraction::evaluate(stack_type& stack) const -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for -"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a - b);
}

auto s22020::rpn_calculator::Multiplication::evaluate(stack_type& stack) const -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for *"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a * b);
}

auto s22020::rpn_calculator::Division::evaluate(stack_type& stack) const -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for /"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a / b);
}

auto s22020::rpn_calculator::Int_Division::evaluate(stack_type& stack) const -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for //"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(floor(a / b));
}

auto s22020::rpn_calculator::Modulo::evaluate(stack_type& stack) const -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for %"};
    }
    int const b = pop_top(stack);
    int const a = pop_top(stack);
    stack.push(a % b);
}

auto s22020::rpn_calculator::Exponentiation::evaluate(stack_type& stack) const -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for **"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(pow(a, b));
}

auto s22020::rpn_calculator::Square_Root::evaluate(stack_type& stack) const -> void {
    if (stack.size() < 1) {
        throw std::logic_error{"not enough operands for sqrt"};
    }
    auto const a = pop_top(stack);
    stack.push(sqrt(a));
}

auto s22020::rpn_calculator::Factorial::evaluate(stack_type& stack) const -> void {
    if (stack.size() < 1) {
        throw std::logic_error{"not enough operands for !"};
    }
    auto const a = pop_top(stack);
    auto tmp     = 1;
    for (int i = a; i > 1; i--) {
        tmp *= i;
    }
    auto const b = tmp;
    stack.push(b);
}

s22020::rpn_calculator::Calculator::Calculator(stack_type s) : stack{std::move(s)}
{}

auto s22020::rpn_calculator::Calculator::push(std::unique_ptr<Element> op) -> void {
    ops.push(std::move(op));
}

/*auto s22020::rpn_calculator::Calculator::push(std::string op) {
    ops.push(std::move(op));
}*/

auto s22020::rpn_calculator::Calculator::evaluate() -> void {
    while (not ops.empty()) {
        // bierze wartosc z poczatku kolejki
        auto op = std::move(ops.front());
        ops.pop();
        // strzalka bo dostaje sie do skladowej do wskaznika alokowanego dynamicznie
        op->evaluate(stack);
    }
}


auto make_args(int argc, char* argv[]) -> std::vector<std::string>
{
    auto args = std::vector<std::string>{};
    std::copy_n(argv, argc, std::back_inserter(args));
    return args;
}


auto main(int argc, char* argv[]) -> int
{
    auto const args = make_args(argc - 1, argv + 1);
    auto stack = std::stack<double>{};
    auto calculator = s22020::rpn_calculator::Calculator{};
    for (auto const each : args) {
        try {
            if (each == "p") {
                calculator.push(std::make_unique<s22020::rpn_calculator::Print>());
            } else if (each == "+") {
                calculator.push(std::make_unique<s22020::rpn_calculator::Addition>());
            } else if (each == "-") {
                calculator.push(std::make_unique<s22020::rpn_calculator::Subtraction>());
            } else if (each == "*") {
                calculator.push(std::make_unique<s22020::rpn_calculator::Multiplication>());
            } else if (each == "/") {
                calculator.push(std::make_unique<s22020::rpn_calculator::Division>());
            } else if (each == "//") {
                calculator.push(std::make_unique<s22020::rpn_calculator::Int_Division>());
            } else if (each == "%") {
                calculator.push(std::make_unique<s22020::rpn_calculator::Modulo>());
            } else if (each == "**") {
                calculator.push(std::make_unique<s22020::rpn_calculator::Exponentiation>());
            } else if (each == "sqrt") {
                calculator.push(std::make_unique<s22020::rpn_calculator::Square_Root>());
            } else if (each == "!") {
                calculator.push(std::make_unique<s22020::rpn_calculator::Factorial>());
            } else {
                calculator.push(std::make_unique<s22020::rpn_calculator::Literal>(std::stod(each)));
            }
        } catch (std::logic_error const& e) {
            std::cerr << "error: " << each << ": " << e.what() << "\n";
        }
    }
    try {
        calculator.evaluate();
    } catch (std::logic_error const& e) {
        std::cerr << "error: during evaluation: " << e.what() << "\n";
    }

    return 0;
}
