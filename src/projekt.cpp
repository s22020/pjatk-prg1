#include <s22020/Projekt.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <typeinfo>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <regex>
#include <fcntl.h>
#include <openssl/aes.h>
#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <cstdio>

//TODO: usun echo, stderr na /dev/null, dodaj (v), pousuwaj pliki .json po stworzeniu .enc, popraw, zeby podawac tylko filename 
s22020::Entry::Entry(std::string t, std::string u, std::string p, std::string url)
    : title{t}, username{u}, password{p}, url{url}
{
}

// zmienic dwa parametry range na az, AZ, num, sp, ktore beda bool
// jesli ktorys true to wsadza znaki z tego zakresu do wektora allowed characters
auto generate_ascii_dec(bool az, bool AZ, bool num, bool chr) -> char {
    // range between 33-126
    // zmien argumenty na opcje, jesli A-Z to range ma byc 96-itp
    auto allowed_characters = std::vector<size_t>{};
    auto az_arr = std::vector<size_t>{};
    auto AZ_arr = std::vector<size_t>{};
    auto num_arr = std::vector<size_t>{};
    auto chr_arr = std::vector<size_t>{};
    chr_arr = {33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,58,59,60,61,62,63,64,91,92,93,94,95,96,123,123,125,126};
    for(int i = 97; i < 123; ++i) {
        az_arr.push_back(i);
    }
    for(int i = 65; i < 91; ++i) {
        AZ_arr.push_back(i);
    }
    for(int i = 48; i < 58; ++i) {
        num_arr.push_back(i);
    }
    if (az) {
        //std::copy_n(az_arr, 26, std::back_inserter(allowed_characters));
        for(int i=0; i<(int)(az_arr.size()); ++i) {
            allowed_characters.push_back(az_arr[i]);
        }
    }
    if (AZ) {
        //std::copy_n(AZ_arr, AZ_arr.size(), std::back_inserter(allowed_characters));
        for(int i=0; i<(int)(AZ_arr.size()); ++i) {
            allowed_characters.push_back(AZ_arr[i]);
        }
    }
    if (num) {
        //std::copy_n(num_arr, num_arr.size(), std::back_inserter(allowed_characters));   
        for(int i=0; i<(int)(num_arr.size()); ++i) {
            allowed_characters.push_back(num_arr[i]);
        }

    }
    if (chr) { 
        //std::copy_n(chr_arr, chr_arr.size(), std::back_inserter(allowed_characters));
        for(int i=0; i<(int)(chr_arr.size()); ++i) {
            allowed_characters.push_back(chr_arr[i]);
        }

    }
    std::random_device dev;
    //std::mt19937 rng(dev());
    std::mt19937 engine(dev());
    //std::uniform_int_distribution<std::mt19937::result_type> dist6(range1,range2);
    std::uniform_int_distribution<int> distribution(0, allowed_characters.size());
    const auto random_number = allowed_characters[distribution(engine)];
    return static_cast<char>(random_number);
}



auto encrypt_file(std::string passphrase, std::string file_name) -> void {
    // tempfile - obiekt json z danymi, ktory ma byc zaszyfrowany na .enc
    system(("openssl aes-256-cbc -in tempfile.json -out "+ file_name +".enc -pass pass:"+passphrase+" 2>/dev/null").c_str());
  /*  CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryptor;
    CryptoPP::AutoSeededRandomPool rnd;
    // Generate a random key
    CryptoPP::SecByteBlock key(0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    rnd.GenerateBlock( key, key.size() );

    // Generate a random IV
    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    rnd.GenerateBlock(iv, iv.size());

    byte plainText[] = "Hello! How are you.";
    size_t messageLen = std::strlen((char*)plainText) + 1;

    //////////////////////////////////////////////////////////////////////////
    // Encrypt

    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption(key, key.size(), iv);
    cfbEncryption.ProcessData(plainText, plainText, messageLen);
*/
    /*int bytes_read, bytes_written;
    unsigned char indata[AES_BLOCK_SIZE];
    unsigned char outdata[AES_BLOCK_SIZE];
    // klucz do szyfrowania i odszyfrowania, moze byc 128 bitow, 192 lub 256 bitow
    const unsigned char ckey[] = "abcdabcdabcdabcd";
     // randomowa wartosc
    unsigned char ivec[] = "testtesttesttest";
    //std::string ivec = "";
    //for (int i = 0; i < 17; ++i) {
    //    ivec += generate_ascii_dec(1,0,1,0);
    }
    FILE *fp;
    //FILE *rp;
    FILE *op;
    //std::ofstream pass_db;
    //std::ofstream temp_file;
    //pass_db.open(file_path, std::ios::out);
    //temp_file.open("./temp.json", std::ios::out);
    fp=fopen("./testme.json","a+b");
    op=fopen("./temp.json","w");
    // struktura danych, ktora zawiera klucz
    AES_KEY key;
    
    // ustanawia klucz
    AES_set_encrypt_key(ckey, 128, &key);

    // ustawia w ktorym miejscu bloku w zaszyfrowanym bloku 128-bitowym zaczac szyfrowanie
    int num = 0;

    while(1) {
        bytes_read = fread(indata, 1, AES_BLOCK_SIZE, fp);

        AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &num, AES_ENCRYPT);
        
        bytes_written = fwrite(outdata, 1, bytes_read, op);

        if (bytes_read < AES_BLOCK_SIZE) {
            break;
        }
    }*/
}


auto decrypt_file(std::string passphrase, std::string file_path) -> void {
    system(("openssl aes-256-cbc -d -in " + file_path + " -pass pass:"+passphrase+" > temp-decr.json").c_str());
}



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

/*auto hide_input() -> void {
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

auto unhide_input() -> void {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}*/

auto main() -> int {
    char option, save_choice; 
    //std::string file_path = "";
    std::cout << "Choose from options ((a)dd entry/(e)dit entry/(d)elete entry) ";
    std::cin >> option;
    //if (option.length() != 1) {
    if (typeid(option).name() != typeid('c').name()) {
        throw std::logic_error{"Invalid option"};
    }
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
            std::string charsets;
            bool az = 0, AZ = 0, num = 0, chr = 0;
            std::cout << "\nChoose character sets: ((s) for [a-z], (b) for [A-Z], (n) for [0-9], (c) for special chars) ";
            std::cin >> charsets;
            if (charsets.length() < 1 && charsets.length() > 4) {
                throw std::logic_error{"Invalid options length"};
            }
            for (int i=0; i<(int)(charsets.length()); ++i) {
                if (charsets[i] == 's') {
                    az = 1;
                } else if (charsets[i] == 'b') {
                    AZ = 1;
                } else if (charsets[i] == 'n') {
                    num = 1;
                } else if (charsets[i] == 'c') {
                    chr = 1;
                } else {
                    throw std::logic_error{"Invalid options provided"};
                }
            }
            std::cout << "\nSelect password length: ";
            std::cin >> pass_length;
            pass = "";
            //auto paswrd = std::string{};
            for (auto i=1; i<=pass_length; ++i) {
                pass += generate_ascii_dec(az, AZ, num, chr);
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
        std::cout << "\nDo you want to save an entry to a file? (y/n) ";
        std::cin >> save_choice;
        if (typeid(save_choice).name() != typeid('c').name() && (save_choice != 'y' || save_choice != 'n')) {
            throw std::logic_error{"Invalid option"};
        }
        // jesli ctrl s albo cos to stworz plik o zadanej nazwie i zapisz do niego
        if (save_choice == 'y') {
            std::string file_path, master_password;
            using namespace nlohmann;
            std::ofstream pass_db;
            std::cout << "Provide file name and path (without an extension)\n";
            std::cin >> file_path;
            std::regex rx(".*\\..*$");
            bool found = std::regex_match(file_path, rx);
            if (found) {
                file_path = "";
                std::cout << "I said, without an extension\n";
                std::cin >> file_path;
            }
            termios oldt;
            tcgetattr(STDIN_FILENO, &oldt);
            termios newt = oldt;
            newt.c_lflag &= ~ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            std::cout << "Provide a master password: ";
            std::cin >> master_password;
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            pass_db.open("tempfile.json", std::ios::out);
            if (pass_db.good()) {
                json jentry = {
                    {"title", entry.title},
                    {"username", entry.username},
                    {"password", entry.password},
                    {"url", entry.url}
                };
                pass_db << jentry.dump() << std::endl;
                 
                pass_db.close();
                encrypt_file(master_password, file_path);
                remove("tempfile.json");
                std::cout << "\nSaved as " + file_path +".enc\n";
            } else {
                throw std::logic_error{"Could not load/create a file"};
            }
        }
    } else if (option == 'e') {
        //edit entry
        using namespace nlohmann;
        std::string file_path,master_password,edit_field, new_value;
        std::ifstream pass_db;
        std::ofstream temp_file;
        std::string line,title;
        json jentry, temp;
        std::cout << "\nProvide a password file path (without an extension): ";    
        std::cin >> file_path;
        termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        std::cout << "\nProvide a master password: ";
        std::cin >> master_password;
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        std::string file_path_ext = file_path + ".enc";
        decrypt_file(master_password, file_path_ext);
        // odszyfrowany plik z obiektem json z danymi
        pass_db.open("temp-decr.json", std::ios::in|std::ios::out);
        if (pass_db.good()) {
            // tworzy nowy plik zeby przekopiowac nowe zmodyfikowane linijki
            temp_file.open("./tempfile.json", std::ios::out);
            std::cout << "\nProvide title to edit an entry: ";
            std::cin >> title;
            std::cout << "\nEnter field to edit (title, username, password, url) ";
            std::cin >> edit_field;
            std::cout << "\nProvide new value: ";
            std::cin >> new_value;
            while (getline(pass_db,line)) {
                if (line.find(title) != std::string::npos) {
                    // tu mozna walnac traja kacza
                    temp = json::parse(line);
                    //std::cout << temp.dump();
                    jentry = json::parse(line);
                    jentry.at(edit_field) = new_value;
                    //std::cout << jentry.dump();
                    // zastap te linijke nowa faza
                    line.replace(line.find(temp.dump()),line.length(),jentry.dump());
                    //std::cout << line;
                }
                temp_file << line << std::endl;
                //line.find(title) >> jentry;
            }
            temp_file.close();
            pass_db.close();
            std::string h = "temp-decr.json";
            const char * p = h.c_str();
            remove(p);
            //rename("./tempfile.json", p);
            encrypt_file(master_password,file_path);
            remove("./tempfile.json");
            
        }
    } else if (option == 'd') {
        //delete entry
        using namespace nlohmann;
        std::string file_path, master_password;
        std::ifstream pass_db;
        std::ofstream temp_file;
        std::string line,title,jentry;
        std::cout << "\nProvide a password file path: (without an extension) ";
        std::cin >> file_path;
        termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        std::cout << "\nProvide a master password: ";
        std::cin >> master_password;
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        std::string file_path_ext = file_path + ".enc";
        decrypt_file(master_password, file_path_ext);
        pass_db.open("temp-decr.json", std::ios::in|std::ios::out);
        if (pass_db.good()) {
            temp_file.open("./tempfile.json", std::ios::out);
            std::cout << "\nProvide title to delete an entry: ";
            std::cin >> title;
            while (getline(pass_db,line)) {
                if (line.find(title) != std::string::npos) {
                    // tu mozna walnac traja kacza
                    jentry = line;
                    line.replace(line.find(jentry),line.length(),"");
                }
                temp_file << line << std::endl;
            }
            temp_file.close();
            pass_db.close();
            std::string h = "temp-decr.json";
            const char * p = h.c_str();
            remove(p);
            //rename("./tempfile.json", p);
            encrypt_file(master_password,file_path);
            remove("./tempfile.json");

        }

    } else {
        std::cout << "Invalid option\n";
    }
    return 0;
}
