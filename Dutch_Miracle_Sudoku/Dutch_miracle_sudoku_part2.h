/*
 *  hint.h
 *  Sudoku
 *  Created by Prof. Ramavarapu Sreenivas 
 *  Inspired by: http://web.eecs.utk.edu/courses/spring2012/cs140/Notes/Sudoku/index.html
*/

#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
#include <tuple>

using std::vector;
using namespace std;
class Sudoku 
{ 
	// Private
	int puzzle[9][9];
	
    int puzzle_copy[9][9];

    int number_of_solutions = 0;

    bool row_valid(int row)
    {
        // write code that checks if "row" is valid
        
        for (int k = 1; k <= 9; k++)
        {
            int count = 0;
            for (int j = 0; j < 9; j++)
            {
                if (puzzle[row][j]==k)
                    count++;
            }
            if (count > 1)
                return false;
        }
        return true;

    }
    
    // Private member function that checks if the named column is valid
    bool col_valid(int col)
    {
        // check validity of "col"
        for (int k = 1; k <= 9; k++)
        {
            int count = 0;
            for (int i = 0; i < 9; i++)
            {
                if (puzzle[i][col]==k)
                    count++;
            }
            if (count > 1)
                return false;
        }
        return true;
    }
    
    // Private member function that checks if the named 3x3 block is valid
    bool block_valid(int row, int col)
    {
        // check 3 x 3 block validity
        int block_row = row / 3; // find which block it is in
        int block_col = col / 3;
        for (int k = 1; k <= 9; k++)
        {
            int count = 0;
            for (int ii = 3*block_row; ii < 3*block_row + 3; ii++)
                for (int jj = 3*block_col; jj < 3*block_col + 3; jj++)
                    if (puzzle[ii][jj] == k)
                        count++;
            if (count > 1)
                return false;
        }
        return true;
    }
    

    


    // Private member function that checks if the positive-diagonal
    // (SW to NE diagonals) have no repeated digits. If the initial
    // partially-filled puzzle does not meet this requirement, I need
    // to flag this (see write-up). I am using tuples for this. This
    // way I can show which value is repeated along the diagonal multiple times
    // I took this from https://stackoverflow.com/questions/321068/returning-multiple-values-from-a-c-function
    
    std::tuple<bool, int> positive_diagonals_valid()
    {
        // write code that checks if there are any repeated
        // digits along the 15-many positive diagonals
        // If the intial puzzle does not meet this requirement,
        // I want to let the user know that digit X has appeared
        // multiple times along some positive diagonal (in the
        // partially-filled input puzzle). This way the user can
        // see the reason why there can be no solution to the
        // Dutch Miracle Sudoku puzzle instance.
        //
        // In my implementation, if the returned bool variable is false,
        // then the second-tuple is the X that was repeated along
        // some positive diagonal (see description of assignment
        // for a sample output).
        
        bool res = true;

        // upper half of the puzzle
        for (int index = 1; index < 9; index++)
        {
            for (int k = 1; k <= 9; k++)
            {
                int count = 0;
                for (int ii = index, jj = 0; ii >= 0 ; ii--, jj++)
                    if (puzzle[ii][jj] == k)
                        count++;
                    
                if (count > 1)
                {
                    res = false;
                    return make_tuple(res,k);
                }
            }
        }
        
        // lower half of the puzzle
        for (int index = 1; index <8; index++)
        {
            for (int k = 1; k <= 9; k++)
            {
                int count = 0;
                for (int jj = index, ii = 8; jj < 9 ; ii--, jj++)
                    if (puzzle[ii][jj] == k)
                        count++;
                    
                if (count > 1)
                {
                    res = false;
                    return make_tuple(res,k);
                }
            }
        }

        return make_tuple(res,0);
    }
    
    // Private member funtion that checks if adjacent cells
    // (along the positive diagonal) touching at a corner
    // have a difference of atleast 4
    std::tuple<bool, int, int> adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4()
    {
        // write code that checks if all non-zero entries in the
        // puzzle (filled so far) have met the "minimum-difference
        // of 4" rule.
        //
        // In my implementation, if the returned bool variable is false,
        // then the two ints (i and j, say) identify puzzle[i][j] and
        // puzzle[i-1][j+1] that do not meet the "minimum-difference
        // of 4" (see program assignment description for a sample output)
        bool res = true;

        for (int index = 1; index < 9; index++)
        {
            for (int ii = index, jj = 0; ii >= 1; ii--, jj++)
            {
                if (puzzle[ii][jj]!=0 && puzzle[ii-1][jj+1]!=0 && abs(puzzle[ii][jj] - puzzle[ii-1][jj+1]) < 4)
                {
                    res = false;
                    return make_tuple(res, ii, jj);
                }
            }
        }
        
        for (int index = 1; index < 8; index++)
        {
            for (int jj = index, ii = 8; jj < 8 ; ii--, jj++)
            {
                if (puzzle[ii][jj]!=0 && puzzle[ii-1][jj+1]!=0 && abs(puzzle[ii][jj] - puzzle[ii-1][jj+1]) < 4)
                {
                    res = false;
                    return make_tuple(res, ii, jj);
                }
            }
        }
        
        return make_tuple(res, 0, 0);
    }
    
	
public:
	// Public member function that reads the incomplete puzzle
	// we are not doing any checks on the input puzzle -- that is,
	// we are assuming they are indeed valid
    void read_puzzle(int argc, char * const argv[])
    {
        // write code that reads the input puzzle using the
        // guidelines of figure 23 of the bootcamp material
        ifstream input_file(argv[1]);

        if (input_file.is_open())
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    input_file >> puzzle[i][j];
                }
            }
        }
        else
            cout << "Input file does not exist" << endl;

        for (int ii = 0; ii < 9; ii++)
            for (int jj = 0; jj<9; jj++)
                puzzle_copy[ii][jj] = puzzle[ii][jj];
    }
	
	// Public member function that prints the puzzle when called
	void print_puzzle()
	{
		//std::cout << number_of_calls << std::endl;
		std::cout << std::endl << "Board Position" << std::endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				// check if we have a legitimate integer between 1 and 9
				if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
				{
					// printing initial value of the puzzle with some formatting
					std::cout << puzzle[i][j] << " ";
				}
				else {
					// printing initial value of the puzzle with some formatting
					std::cout << "X ";
				}
			}
			std::cout << std::endl;
		}
	}
    
    // Public member function that (recursively) implements the brute-force
    // search for possible solutions to the incomplete Sudoku puzzle
    bool Solve(int row, int col)
    {
        // this part of the code identifies the row and col number of the
        // first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
        // no zeros, the variable row will be 9 => the puzzle is done, as
        // each entry is row-, col- and block-valid...
        
        // use the pseudo code of figure 3 of the description

        if (row==0 && col==0) // check the initial puzzle
        {
            if (get<0>(positive_diagonals_valid()) == false || get<0>(adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4()) == false)
            {
                cout << "Partially-Filled Sudoku Puzzle does not meet Dutch Miracle requirements" << endl;
                if (get<0>(positive_diagonals_valid()) == false)
                    cout << "The number " << get<1>(positive_diagonals_valid()) << " appears multiple times along the positive diagonal" << endl;
                if (get<0>(adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4()) == false)
                {
                    int x = get<1>(adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4());
                    int y = get<2>(adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4());
                    cout << "Puzzle[" << x << "]" << "[" << y << "]" << " = " << puzzle[x][y] << "," 
                    << " Puzzle[" << x-1 << "]" << "[" << y+1 << "]" << " = " << puzzle[x-1][y+1]
                    << ", and they do not meet the minimum difference of 4" << endl;
                }
                return false;
            }
        }

        while (row < 9 && puzzle[row][col] != 0)  // find the next unfilled position
        {
            col++;
            if (col == 9)
            {
                row++;
                col = 0;
            }
        }
        
        if (row == 9)
        {
            number_of_solutions++;
            cout << endl << "Solution #" << number_of_solutions;
            print_puzzle();
            return true;
        }
        
        bool found_solution = false;

        for (int k = 1; k <= 9; k++)
        {
            puzzle[row][col] = k;
            if (row_valid(row) && col_valid(col) && block_valid(row,col) && get<0>(positive_diagonals_valid()) && get<0>(adjacent_cells_along_positive_diagonals_have_at_least_a_difference_of_4()) && Solve(row,col))
                found_solution = true;
            
            for (int ii = row; ii < 9; ii++)
                for (int jj = col; jj<9; jj++)
                    puzzle[ii][jj] = puzzle_copy[ii][jj];
            
        }

        if (found_solution)
             return true;

        puzzle[row][col] = 0;
        return false;



    }
};

#endif
