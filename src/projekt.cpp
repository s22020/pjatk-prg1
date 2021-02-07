#include <s22020/Projekt.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <typeinfo>
#include <fstream>

s22020::Entry::Entry(std::string t, std::string u, std::string p, std::string url)
    : title{t}, username{u}, password{p}, url{url}
{
}

auto generate_ascii_dec(unsigned range1, unsigned range2) -> char {
    // range between 32-126
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(range1,range2);
    return static_cast<char>(dist6(rng));
}

/*auto autogenerate() -> int {}*/

auto main() -> int {
    char option; 
    std::cout << "Choose from options ((a)dd entry/(e)dit entry/(d)elete entry) ";
    std::cin >> option;
    std::cout << typeid(option).name();
    //if (option.length() != 1) {
    if (typeid(option).name() != typeid('c').name()) {
        throw std::logic_error{"Invalid option"};
    }
/*    option = std::stoi(option);
    switch(option) {
        case 65: case 97:
            //add entry
            break;
        case 69: case 101:
            //edit entry
            break;
        case 69: case 100:
            //delete entry
            break;
        default:
            std::cout << "Invalid option";
    }*/
    if (option == 'a') {
        //add entry
        std::string title;
        std::string user;
        std::string pass;
        std::string url;
        std::cout << "A\n";
        std::cout << "Title: ";
        std::cin >> title;
        std::cout << "Username: ";
        std::cin >> user;
        std::cout << "Password: (type g to autogenerate) ";
        /*if (pass == 'g') {
            autogenerate();
        }*/
        std::cin >> pass;
        std::cout << "URL: ";
        std::cin >> url;
        auto test = s22020::Entry{title,user,pass,url};
        std::cout << test.username;
        // jesli ctrl s albo cos to stworz plik o zadanej nazwie i zapisz do niego
        /*std::fstream MyFile("filename.txt");
        MyFile << "Title: " << test.title << "\n" << "User: " << test.username << "\n" << 
        "Password: " << test.password << "\n" << "URL: " << test.url << "\n";
        MyFile.std::close();
        // Czytanie z pliku:
        std::string myText;
        std::ifstream MyReadFile("filename.txt");
        while(std::getline(MyReadFile, myText)) {
            std::cout << myText;
        }
        myReadFile.std::close();
        */
    } else if (option == 'e') {
        //edit entry
        std::cout << "E";
    } else if (option == 'd') {
        //delete entry
        std::cout << "D";
    } else {
        std::cout << "Invalid option\n";
    }
    // if no entries to nie mozna edit albo delete
    // if new entry to tworzy obiekt Entry z polami title, user, password, url,
    // jesli password to wcisnij (g) zeby autogenerate
    // jesli autogenerate to wpisz kolejno: dlugosc, (u)ppercase, (l)owercase, (n)umbers, (c)haracters 
    // dlugosc - count
    // jesli nie wpisze sie /save, to bedzie *, jesli save to podaj haslo i zapisuje jako db, kluczem haslo
    // jak zrobic laczony range?
    //auto a = system("od -vAn -N2 -tu2 < /dev/urandom");
    //std::cout << a << std::endl;
    //std::cout << srand((int) a) % 100;
    /*std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(32,126);
    std::cout << static_cast<char>(dist6(rng)) << std::endl;*/
    /*auto test = generate_ascii_dec(33,34);
    std::cout << test << std::endl;
    std::cout << "======================" << std::endl;
    char c = 'a';
    std::cout << typeid(c).name();*/
    return 0;
}
