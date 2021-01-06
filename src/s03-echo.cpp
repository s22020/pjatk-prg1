#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    if (argc < 2) {
        throw std::logic_error{"Insufficient arguments provided.\n"};
    }

    auto args = std::vector<std::string>{};
    // kopiowanie argc elementów argv do wektora args przez dołączanie elementów
    std::copy_n(argv, argc, std::back_inserter(args));
    auto first_arg     = std::string{argv[1]};
    auto scnd_arg      = std::string{argv[2]};
    auto delimiter     = " ";
    auto end_delimiter = "\n";

    if ((first_arg == "-n") || (scnd_arg == "-n")) {
        end_delimiter = "";
    }

    if (first_arg == "-l" || scnd_arg == "-l") {
        delimiter     = "\n";
        end_delimiter = "";
    }

    if (first_arg == "-r" || scnd_arg == "-r") {
        std::reverse(args.begin(), args.end());
    }


    // for (int i=0; i < args, ++i) {
    for (auto const& each : args) {
        std::cout << each << delimiter;
    }
    std::cout << end_delimiter;

    return 0;
}
