#pragma once

#include <bitset>

class Solver
{
public:
    void solve();
    std::string getstate();

    // Initialize all bitboards
    Solver(const std::string& key)
    {
        rows[0] = 0b111111111;
        rows[1] = rows[0] << 9;
        rows[2] = rows[1] << 9;
        rows[3] = rows[2] << 9;
        rows[4] = rows[3] << 9;
        rows[5] = rows[4] << 9;
        rows[6] = rows[5] << 9;
        rows[7] = rows[6] << 9;
        rows[8] = rows[7] << 9;

        columns[0] = 0b1;
        columns[0] = columns[0] | (columns[0] << 9) | (columns[0] << 18)
            | (columns[0] << 27) | (columns[0] << 36)
            | (columns[0] << 45) | (columns[0] << 54)
            | (columns[0] << 63) | (columns[0] << 72);
        columns[1] = columns[0] << 1;
        columns[2] = columns[1] << 1;
        columns[3] = columns[2] << 1;
        columns[4] = columns[3] << 1;
        columns[5] = columns[4] << 1;
        columns[6] = columns[5] << 1;
        columns[7] = columns[6] << 1;
        columns[8] = columns[7] << 1;

        grids[0] = (0b111) | (0b111 << 9) | (0b111 << 18);
        grids[1] = grids[0] << 3;
        grids[2] = grids[1] << 3;
        grids[3] = grids[0] << 27;
        grids[4] = grids[3] << 3;
        grids[5] = grids[4] << 3;
        grids[6] = grids[3] << 27;
        grids[7] = grids[6] << 3;
        grids[8] = grids[7] << 3;

        for (int i = 0; i < 81; i++)
        {
            if (key.at(i) == '0' || key.at(i) == '.')
                empty.set(i);
            else if (key.at(i) == '1')
                bitboards[0].set(i);
            else if (key.at(i) == '2')
                bitboards[1].set(i);
            else if (key.at(i) == '3')
                bitboards[2].set(i);
            else if (key.at(i) == '4')
                bitboards[3].set(i);
            else if (key.at(i) == '5')
                bitboards[4].set(i);
            else if (key.at(i) == '6')
                bitboards[5].set(i);
            else if (key.at(i) == '7')
                bitboards[6].set(i);
            else if (key.at(i) == '8')
                bitboards[7].set(i);
            else if (key.at(i) == '9')
                bitboards[8].set(i);
        }

        // Puzzle is assumed to be not solved
        solved = false; 
    }

private:
    // Bitmasks for each row
    std::bitset<81> rows[9];
    // Bitmasks for each column
    std::bitset<81> columns[9];
    // Bitmasks for each grid
    std::bitset<81> grids[9];
    // Bitboard for each number, empty contains empty spaces
    std::bitset<81> bitboards[9];
    std::bitset<81> empty;

    bool solved;

    void eliminateSolve();
};