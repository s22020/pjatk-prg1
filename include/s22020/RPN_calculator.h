#ifndef S22020_RPN_CALCULATOR_H
#define S22020_RPN_CALCULATOR_H

#include <memory>
#include <queue>
#include <stack>


namespace s22020 {
namespace rpn_calculator {
using stack_type = std::stack<double>;

struct Element {
    // virtual - funkcja ktora jest funkcja skladowa klasy z ktorej dziedzicze i nadpisywana w klasie dziedziczonej
    // uzywa sie jej, zeby bez problemu potem uzywac tej samej funkcji w klasach i ich pochodnych, ale np.
    // robic  tak, by wykonywaly rozne rzeczy
    virtual auto evaluate(stack_type&) const -> void = 0;
    // destruktor - w sumie nie jest w ogole potrzebny w prostych klasach, ale jak sie dynamicznie alokuje
    // pamiec, to dobrze, zeby byl, w razie gdyby program zakonczyl sie szybciej niz zostanie zniszczony obiekt
    // jest to funkcja, ktora wykonuje sie w momencie gdy obiekt danej klasy jest niszczony
    virtual ~Element();
};

struct Literal : public Element {
    double const value{0.0};

    // override - nadpisuje odziedziczona metode 
    auto evaluate(stack_type&) const -> void override;

    Literal(double const);
};

struct Print : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Addition : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Subtraction : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Multiplication : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Division : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Int_Division : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Modulo : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Exponentiation : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Square_Root : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Factorial : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Calculator {
    stack_type stack;
    //unique_ptr - jest po to, zeby zajal sie za mnie zwolnieniem pamieci, jest to struktura danych, ktora
    //przechowuje wskaznik i jak wyjdzie unique_ptr poza zakres to uruchomi destruktor na strukturze danych
    //do ktorej przechowuje wskaznik, czyli to tak samo jak zwykla zmienna, ale ta zmienna moze byc zaalokowana
    //dynamicznie. sluzy tez do przenoszenia i kopiowania struktur danych, z ktorymi normalnie nie da sie tak zrobic
    //np std::thread
    std::queue<std::unique_ptr<Element>> ops;

    auto push(std::unique_ptr<Element>) -> void;

    /*auto push(std::string) -> void;
*/
    auto evaluate() -> void;

    Calculator() = default;
    Calculator(stack_type);
};
}}  // namespace s22020::rpn_calculator

#endif
