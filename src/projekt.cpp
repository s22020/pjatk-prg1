#include <s22020/Projekt.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <typeinfo>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <openssl/aes.h>
#include <cmath>
#include <vector>
#include <regex>

s22020::Entry::Entry(std::string t, std::string u, std::string p, std::string url)
    : title{t}, username{u}, password{p}, url{url}
{
}

// zmienic dwa parametry range na az, AZ, num, sp, ktore beda bool
// jesli ktorys true to wsadza znaki z tego zakresu do wektora allowed characters
auto generate_ascii_dec(unsigned range1, unsigned range2) -> char {
    // range between 33-126
    // zmien argumenty na opcje, jesli A-Z to range ma byc 96-itp
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(range1,range2);
    return static_cast<char>(dist6(rng));
}


/*auto autogenerate(bool a, bool B, bool n, bool c) -> int {
    randutils::mt19937_rng rng;
    int foo[36] = {33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,58,59,60,61,62,63,64,91,92,93,94,95,96,123,124,125,126};
    if (c) {
        auto result = rng.pick(foo);
    }
    return result;
}*/

/*auto encrypt_file() -> void {
    int bytes_read, bytes_written;
    unsigned char indata[AES_BLOCK_SIZE];
    unsigned char outdata[AES_BLOCK_SIZE];
    // klucz do szyfrowania i odszyfrowania, moze byc 128 bitow, 192 lub 256 bitow
    const unsigned char ckey[] = "abcdabcdabcdabcd";
    unsigned char ivec[] = "testtesttesttest";

    // struktura danych, ktora zawiera klucz
    AES_KEY key;
    
    // ustanawia klucz
    AES_set_encrypt_key(ckey, 128, &key);

    // ustawia w ktorym miejscu bloku w zaszyfrowanym bloku 128-bitowym zaczac szyfrowanie
    int num = 0;

    while(1) {
        bytes_read = fread(indata, 1, AES_BLOCK_SIZE, "test");

        AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &num, AES_ENCRYPT);
        
        bytes_written = fwrite(outdata, 1, bytes_read, "test2");

        if (bytes_read < AES_BLOCK_SIZE) {
            break;
        }
    }
}

auto decrypt_file() -> void {
    int bytes_read, bytes_written;
    unsigned char indata[AES_BLOCK_SIZE];
    unsigned char outdata[AES_BLOCK_SIZE];
    // klucz do szyfrowania i odszyfrowania, moze byc 128 bitow, 192 lub 256 bitow
    unsigned char ckey[] = "abcdabcdabcdabcd";
    unsigned char ivec[] = "testtesttesttest";

    // struktura danych, ktora zawiera klucz
    AES_KEY key;

    // ustanawia klucz
    AES_set_encrypt_key(ckey, 128, &key);

    // ustawia w ktorym miejscu bloku w zaszyfrowanym bloku 128-bitowym zaczac szyfrowanie
    int num = 0;

    while(1) {
        bytes_read = fread(indata, 1, AES_BLOCK_SIZE, ifp);

        AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &num, AES_DECRYPT);

        bytes_written = fwrite(outdata, 1, bytes_read, ofp);

        if (bytes_read < AES_BLOCK_SIZE) {
            break;
        }
    }
}*/


// kazdy argument to czy istnieje znak z danego zakresu znakow
auto calculate_n_charset(std::string phrase) -> int {
    bool az = false, AZ = false, num = false, spchar = false;
    for (int i = 0; i < int(phrase.length()); ++i) {
        if (phrase[i] >= 'a' && phrase[i] <= 'z') {
           az = true;
        } else if (phrase[i] >= 'A' && phrase[i] <= 'Z') {
           AZ = true;
        } else if (phrase[i] >= '0' && phrase[i] <= '9') {
           num = true;
        } else {
           spchar = true;
        }
    }
    int small_alpha = 26 * int(az);
    int capital_alpha = 26 * int(AZ);
    int numerical = 10 * int(num);
    int special_chars = 32 * int(spchar);
    return small_alpha + capital_alpha + numerical + special_chars;
}

// jako argument ma przyjac zbior danych w int oraz liczbe znakow w int, 
// wczesniej w funkcji autogenerate zestaw znakow ma byc w if else
// i na tej podstawie ma byc okreslona kolekcja
// w return obliczona entropia lub w cout
auto calculate_entropy(int collection, int n) -> float {
    // logarytm stropnia 2
    float entropy = (log(collection)/log(2)) * n;
    std::string strength;
    // maksymalna liczba kombinacji potrzebna do zlamania hasla:
    // 2^liczba_entropii_bitow_hasla
    // obliczanie liczby bitow entropii w jednym znaku (prawpodobienstwo wystapienia kazdego ze znakow jest takie samo):
    // H(x) = log2(n)
    // n - liczba wszystkich znakow w danym zbiorze
    // ten wzor sie tyczy entropii w jednym zestawie znakow, np [a-z]
    // a liczenie entropii dla calego hasla z danego zestawu znakow to
    // entropia jednego znaku * liczba znakow w hasle
    // dla zbiorow skladajacych sie z wielu znakow
    // n - liczba wszystkich znakow w danym zbiorze, czyli np [a-z][0-9] to bedzie 26 + 10 = 36
    // float log(float x); - logarytm
    if (entropy < 56) {
        strength = "very weak";
    } else if (entropy >= 56 && entropy < 67) {
        strength = "weak";
    } else if (entropy >= 67 && entropy < 78) {
        strength = "moderate";
    } else if (entropy >= 78 && entropy < 91) {
        strength = "good";
    } else if (entropy >= 91 && entropy < 110) {
        strength = "strong";
    } else {
        strength = "very strong";
    }
    std::cout << "\nPassword's entropy is " << entropy << " bits (" << strength << ")";
    return entropy;
}

auto main() -> int {
    char option, save_choice; 
    std::cout << "Choose from options ((a)dd entry/(e)dit entry/(d)elete entry) ";
    std::cin >> option;
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
        std::string title, user, pass, url;
        std::cout << "Title: ";
        std::cin >> title;
        std::cout << "Username: ";
        std::cin >> user;
        //http://www.cplusplus.com/forum/beginner/43683/
        //cover password field
        termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        std::cout << "Password: (type g and <ENTER> to autogenerate) ";
        std::cin >> pass;
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        if (pass == "g") {
            int pass_length;
            std::cout << "\nSelect password length: ";
            std::cin >> pass_length;
            pass = "";
            //auto paswrd = std::string{};
            for (auto i=1; i<=pass_length; ++i) {
                pass += generate_ascii_dec(33,126);
            }
            std::cout << pass << std::endl;
            auto n_charset = calculate_n_charset(pass);
            calculate_entropy(n_charset, pass_length);
        } else {
            auto n_charset = calculate_n_charset(pass);
            calculate_entropy(n_charset, pass.length());
        }
        //SetConsoleMode(hStdin, mode);
        std::cout << "\nURL: ";
        std::cin >> url;
        auto entry = s22020::Entry{title,user,pass,url};
        std::cout << entry.password;
        std::cout << "\nDo you want to save an entry to a file? (y/n) ";
        std::cin >> save_choice;
        if (typeid(save_choice).name() != typeid('c').name() && (save_choice != 'y' || save_choice != 'n')) {
            throw std::logic_error{"Invalid option"};
        }
        // jesli ctrl s albo cos to stworz plik o zadanej nazwie i zapisz do niego
        if (save_choice == 'y') {
            std::string file_path;
            std::cout << "Provide file name and path\n";
            std::cin >> file_path;
            auto pass_db = open(file_path.c_str(), O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
            auto buf = std::string{"Title: " + entry.title + "\n" + "User: " + entry.username + "\n" + 
            "Password: " + entry.password + "\n" + "URL: " + entry.url + "\n"};
            auto n = write(pass_db, buf.data(), buf.size());
            //std::cout << buf.data() << buf.size();
            if (n == -1) {
                perror("write(2)");
            }
            close(pass_db);
            // Czytanie z pliku:
            /*std::string myText;
            std::ifstream MyReadFile("filename.txt");
            while(std::getline(MyReadFile, myText)) {
                std::cout << myText;
            }
            myReadFile.std::close();*/
        }
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
    return 0;
}
