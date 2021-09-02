#pragma once

#include <bitset>
#include <iostream>

struct State
{
    // Bitboard for each number, empty contains empty spaces
    std::bitset<81> bitboards[9];
    std::bitset<81> empty;
};

class Solver
{
public:
    bool solve(int row, int col);
    std::string get_state();

    // Initialize all bitboards
    Solver(const std::string& key)
    {
        for (int r = 0; r < 9; r++)
        {
            for (int c = 0; c < 9; c++)
            {
                int square = r * 9 + c;
                int g = r / 3 % 3 * 3 * 9 + c / 3 % 3 * 3;
                for (int i = 0; i < 9; i++)
                {
                    square_masks[square].set(r * 9 + i);                // Row mask
                    square_masks[square].set(i * 9 + c);                // Column mask
                    square_masks[square].set(g + i / 3 * 9 + i % 3);    // Grid mask
                }
            }
        }

        for (int i = 0; i < 81; i++)
        {
            if (key.at(i) == '0' || key.at(i) == '.')
                state.empty.set(i);
            else if (key.at(i) == '1')
                state.bitboards[0].set(i);
            else if (key.at(i) == '2')
                state.bitboards[1].set(i);
            else if (key.at(i) == '3')
                state.bitboards[2].set(i);
            else if (key.at(i) == '4')
                state.bitboards[3].set(i);
            else if (key.at(i) == '5')
                state.bitboards[4].set(i);
            else if (key.at(i) == '6')
                state.bitboards[5].set(i);
            else if (key.at(i) == '7')
                state.bitboards[6].set(i);
            else if (key.at(i) == '8')
                state.bitboards[7].set(i);
            else if (key.at(i) == '9')
                state.bitboards[8].set(i);
        }
    }
    State state;
    std::bitset<81> square_masks[81];

    inline bool is_safe(int num, int row, int col)
    {
        return (square_masks[row * 9 + col] & state.bitboards[num]).none();
    }
};