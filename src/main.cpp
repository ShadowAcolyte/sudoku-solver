#include <iostream>
#include <bitset>
#include "color.hpp"
#include "solver.h"
#include "benchmark.h"

//test key: 004962300060100400820370006001406020002750000093200704270030940100000275900820001

void display(const std::string& key)
{
    for (int i = 0; i < 81; i ++) {
        if (i % 9 == 0)
            std::cout << "\n+---+---+---+---+---+---+---+---+---+\n|";
        std::cout << " " << hue::light_purple;;
        if (key.at(i) == '0' || key.at(i) == '.')
            std::cout << " ";
        else
            std::cout << key.at(i);
        std::cout << hue::reset << " |";;
    }
    std::cout << "\n+---+---+---+---+---+---+---+---+---+\n";
}

void display(const std::string& key, const std::string& solvedkey)
{
    for (int i = 0; i < 81; i ++) {
        if (i % 9 == 0)
            std::cout << "\n+---+---+---+---+---+---+---+---+---+\n|";
        std::cout << " ";
        if (key.at(i) == '0' || key.at(i) == '.')
            std::cout << hue::light_green << solvedkey.at(i);
        else
            std::cout << hue::light_purple << key.at(i);
        std::cout << hue::reset << " |";;
    }
    std::cout << "\n+---+---+---+---+---+---+---+---+---+\n";
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
    std::string key(argv[1]);
    if (key.length() != 81) {
        std::cout << dye::light_red("ERROR: Key length must be 81 digits!\n");
        return -1;
    }

    if (key.find_first_not_of("0123456789.") != std::string::npos) {
        std::cout << dye::light_red("ERROR: Key can only contain numbers and dots('.')\n");
        return -1;
    }

    std::cout << "Original Board: \n";
    display(key);

    benchmark b;
    Solver solver{key};
    solver.solve();
    b.reset();

    std::cout << "\nSolved Board: \n";
    display(key, solver.getstate());
}