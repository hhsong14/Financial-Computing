#ifndef N_queens_part2
#define N_queens_part2
using namespace std;
class Board
{
	
	// private data member: size of the board
	int size;
    
    // pointer-to-pointer initialization of the board
	int **chess_board;
	
	// number of solutions
	int sol_num = 0;

	// private member function:  returns 'false' if
	// the (row, col) position is not safe.
	bool is_this_position_safe(int row, int col)
	{
		// write the appropriate code on your own that returns
		// "true" if the (row,col) position is safe.  If it is 
		// unsafe (i.e. some other queen can threaten this position)
		// return "false"

		int i,j;
		// Only need to check the left side
		// check the row
		for ( i = 0; i < col; i++)
		{
			if (chess_board[row][i]==1)
				return false;
		}
		
		// check the upper diagonal
		for ( i = row, j = col; i >= 0 && j >= 0; i--, j--)
		{
			if (chess_board[i][j]==1)
				return false;
		}

		// check the lower diagonal
		for ( i = row, j = col; i < size && j >= 0; i++, j--)
		{
			if (chess_board[i][j]==1)
				return false;
		}

		return true;
	}
	
	// private member function: initializes the (n x n) chessboard 
	void initialize(int n)
	{
		
		// write the appropriate code that uses the pointer-to-pointer 
		// method to initialize the (n x n) chessboard.  Once initialized,
		// put zeros in all entries.  Later on, if you placed a queen in
		// the (i,j)-th position, then chessboard[i][j] will be 1.  
		size = n; 
		chess_board = new int*[size];
		int i,j;
		for ( i = 0; i < size; i++)
		{
			chess_board[i] = new int[size];
		}

		for ( i = 0; i < size; i++)
			for (j = 0; j < size; j++)
				chess_board[i][j] = 0;
		
	}
	
	// private member function: prints the board position
	void print_board()
	{
        std::cout << size << "-Queens Problem Solution" << std::endl;
		// write the appropriate code here to print out the solved 
		// board as shown in the assignment description
		int i,j;
		for (i = 0; i<size ; i++)
			std::cout << "---" ;
		std::cout << std::endl;

		for (i = 0; i<size ; i++)
		{
			for (j = 0; j<size ; j++)
			{
				if (chess_board[i][j] == 1)
					std::cout << " Q " ;
				else 
					std::cout << " - " ;
			}
			std::cout << std::endl;
		}

		for (i = 0; i<size ; i++)
			std::cout << "---" ;
		std::cout << std::endl;
	}
	
	// private member function: recursive backtracking
	bool solve(int col)
	{
		// implement the recursive backtracking procedure described in 
		// pseudocode format in figure 1 of the description of the first
		// programming assignment

		if (col == size)
		{
			print_board();
			sol_num++;
			return true;
		}
		

		for (int i=0; i < size; i++)
		{
			if (is_this_position_safe(i,col))
			{
				chess_board[i][col] = 1; // place
				solve(col+1); // next column
		
				chess_board[i][col] = 0; // remove
			}
				
		}
		return false;
	}
	
public:
	// Solves the n-Queens problem by (recursive) backtracking
	void nQueens(int n)
	{
		initialize(n);
		
		solve(0);
		if (sol_num == 0)
			std::cout << "There is no solution to the " << n << "-Queens Problem" << std::endl;
		else
			std::cout << "There are " << sol_num << " different solutions to the " << n << "-Queens Problem" << std::endl;
		
	}
};
#endif