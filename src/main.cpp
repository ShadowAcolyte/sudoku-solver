#include <iostream>
#include <chrono>
#include <bitset>
#include "color.hpp"
#include "solver.h"

//test key: 004962300060100400820370006001406020002750000093200704270030940100000275900820001

using std::string;
using std::chrono::duration_cast, std::chrono::milliseconds, std::chrono::system_clock;

void display(const string& key)
{
    for (int i = 0; i < 81; i ++) {
        if (i % 9 == 0)
            std::cout << "\n+ - + - + - + - + - + - + - + - + - +\n|";
        std::cout << " " << hue::light_purple;;
        if (key.at(i) == '0' || key.at(i) == '.')
            std::cout << " ";
        else
            std::cout << key.at(i);
        std::cout << hue::reset << " |";;
    }
    std::cout << "\n+ - + - + - + - + - + - + - + - + - +\n";
}

void display(const string& key, const string& solvedkey)
{
    for (int i = 0; i < 81; i ++) {
        if (i % 9 == 0)
            std::cout << "\n+ - + - + - + - + - + - + - + - + - +\n|";
        std::cout << " ";
        if (key.at(i) == '0' || key.at(i) == '.')
            std::cout << hue::light_green << solvedkey.at(i);
        else
            std::cout << hue::light_purple << key.at(i);
        std::cout << hue::reset << " |";;
    }
    std::cout << "\n+ - + - + - + - + - + - + - + - + - +\n";
}

int main(int argc, char** argv)
{
    std::cout << "\nSudoku Solver " << dye::light_green("[Version 1.0.0]\n");
    std::cout << "Author: " << dye::aqua("ShadowAcolyte\n");
    std::cout << dye::aqua("https://github.com/ShadowAcolyte\n\n");

    if (argc == 1) {
        std::cout << dye::light_red("ERROR: No key specified!\n");
        return -1;
    }
    string key(argv[1]);
    if (key.length() != 81) {
        std::cout << dye::light_red("ERROR: Key length must be 81 digits!\n");
        return -1;
    }

    if (key.find_first_not_of("0123456789.") != string::npos) {
        std::cout << dye::light_red("ERROR: Key can only contain numbers and dots('.')\n");
        return -1;
    }

    std::cout << "Original Board: \n";
    display(key);

    uint64_t t_start, t_end;
    t_start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    Solver solver{key};
    solver.solve();
    t_end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    std::cout << "\nSolved Board: \n";
    display(key, solver.getstate());
    std::cout << "Time taken: " << t_end - t_start << "ms" << std::endl;
}