#include <iostream>
#include <sstream>
#include "solver.h"

void Solver::eliminateSolve()
{
    /*
      Bitboards for valid locations for each number from 1 to 9
      using row, grid and column elimnation.
    */
    std::bitset<81> valid[9];

    // Finding valid loactions for digit '1'
    /*
      The first step is to eliminate the columns and rows which have the digit '1' in them,
      as well as the 3x3 grids which have the digit '1' in them.
      For example, if the bitboard for '1' looks like this:
      0 0 0 0 0 0 0 0 0
      0 0 0 0 0 0 0 0 0
      0 0 1 0 0 0 0 0 0
      0 0 0 0 0 0 0 0 0
      0 0 0 0 0 0 0 0 0
      0 0 0 0 0 0 0 0 0
      0 0 0 0 0 0 1 0 0
      0 0 0 0 0 0 0 0 0
      0 0 0 0 0 0 0 0 0

      After the first set of operations(to eliminate the rows and columns) a new bitboard would be created:
      0 0 1 0 0 0 1 0 0
      0 0 1 0 0 0 1 0 0
      1 1 1 1 1 1 1 1 1
      0 0 1 0 0 0 1 0 0
      0 0 1 0 0 0 1 0 0
      0 0 1 0 0 0 1 0 0
      1 1 1 1 1 1 1 1 1
      0 0 1 0 0 0 1 0 0
      0 0 1 0 0 0 1 0 0

      After the second set of operations to remove the grids:
      1 1 1 0 0 0 1 0 0
      1 1 1 0 0 0 1 0 0
      1 1 1 1 1 1 1 1 1
      0 0 1 0 0 0 1 0 0
      0 0 1 0 0 0 1 0 0
      0 0 1 0 0 0 1 0 0
      1 1 1 1 1 1 1 1 1
      0 0 1 0 0 0 1 1 1
      0 0 1 0 0 0 1 1 1

      The inverse(not operator) of this bitboard would give us the valid locations for the digit '1'.
      The same applies to bitboards of all the other digits.
      */
    for (int n = 0; n < 9; n++) {
        // Find columns with digit 'n'
        valid[n] = (bitboards[n] | (bitboards[n] << 9) | (bitboards[n] << 18)
            | (bitboards[n] << 27) | (bitboards[n] << 36)
            | (bitboards[n] << 45) | (bitboards[n] << 54)
            | (bitboards[n] << 63) | (bitboards[n] << 72));
        valid[n] |= (bitboards[n] | (bitboards[n] >> 9) | (bitboards[n] >> 18)
            | (bitboards[n] >> 27) | (bitboards[n] >> 36)
            | (bitboards[n] >> 45) | (bitboards[n] >> 54)
            | (bitboards[n] >> 63) | (bitboards[n] >> 72));
        for (int i = 0; i < 9; i++) {
            // Find rows with digit 'n'
            if ((bitboards[n] & rows[i]).any())
                valid[n] |= rows[i];
            // Find grids with digit 'n'
            if ((bitboards[n] & grids[i]).any())
                valid[n] |= grids[i];
        }
        // Invert the bitboard and compare with empty cells to get valid locations
        valid[n] = ~valid[n] & empty;
    }

    /*
      If there is only one valid location in a particular row, column or grid,
      for a particular digit, then that is the only possilbe digit in that location.

      For example consider the follwing bitboard:
      1 0 0 0 0 0 0 0 0
      1 0 0 0 1 0 0 0 0
      0 0 0 0 0 0 0 0 0
      0 0 0 0 0 0 0 0 0
      0 0 0 0 0 0 0 0 0
      0 0 0 0 0 0 0 0 0
      0 0 0 0 0 0 0 0 0
      0 0 0 0 0 0 0 0 0
      0 0 0 0 0 0 0 0 0

      Even though there are two possible locations for '1' in the 1st column, it
      can only be in the 1st row because if it were in the 2nd row, then the 1st row
      would have no '1's in it. However, the 2nd row still has space for a '1' at the
      5th column. Note, we know there wont be any other '1's in the first row because
      the valid bitboard is created such that valid locations for '1' cannot be in rows,
      columns or grids which already have a '1' in them.

      We do the same check for each column and grid as well.
    */
   for (int n = 0; n < 9; n++) {
       for (int i = 0; i < 9; i++) {
           // Row check
            if ((valid[n] & rows[i]).count() == 1)
                bitboards[n] |= valid[n] & rows[i];
            // Column check
            if ((valid[n] & columns[i]).count() == 1)
                bitboards[n] |= valid[n] & columns[i];
            // Grid check
            if ((valid[n] & grids[i]).count() == 1)
                bitboards[n] |= valid[n] & grids[i];
       }
   }
    std::bitset<81> temp = ~(bitboards[0] | bitboards[1] | bitboards[2]
                           | bitboards[3] | bitboards[4] | bitboards[5]
                           | bitboards[6] | bitboards[7] | bitboards[8]);
    if (temp == empty)
        return;
    empty = temp;
    eliminateSolve();
}

void Solver::solve()
{
    eliminateSolve();
    empty = ~(bitboards[0] | bitboards[1] | bitboards[2]
            | bitboards[3] | bitboards[4] | bitboards[5]
            | bitboards[6] | bitboards[7] | bitboards[8]);
}

std::string Solver::getstate()
{
    std::stringstream ss;
    for (int i = 0; i < 81; i++) {
        if (empty[i]) {
            ss << ' ';
            continue;
        }
        for (int n = 0; n < 9; n++) {
            if (bitboards[n][i])
                ss << n + 1;
        }
    }
    return ss.str();
}
