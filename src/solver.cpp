#include <bitset>
#include <cstdint>
#include <iostream>
#include <sstream>
#include "solver.h"

bool Solver::solve(int row, int col)
{
    state.empty = ~(state.bitboards[0] | state.bitboards[1] | state.bitboards[2]
            | state.bitboards[3] | state.bitboards[4] | state.bitboards[5]
            | state.bitboards[6] | state.bitboards[7] | state.bitboards[8]);
    
    if (row == 8 && col == 9)
        return true;
    if (col == 9)
    {
        row++;
        col = 0;
    }
    if (!state.empty[row * 9 + col])
        return solve(row, col + 1);
    
    State old_state = state;
    for (int n = 0; n < 9; n++)
    {
        if (is_safe(n, row, col))
        {
            state.bitboards[n].set(row * 9 + col);
            if (solve(row, col + 1))
                return true;
        }
        state = old_state;
    }

    return false;
}

std::string Solver::get_state()
{
    std::stringstream ss;
    for (int i = 0; i < 81; i++) {
        if (state.empty[i]) {
            ss << ' ';
            continue;
        }
        for (int n = 0; n < 9; n++) {
            if (state.bitboards[n][i])
                ss << n + 1;
        }
    }
    return ss.str();
}
