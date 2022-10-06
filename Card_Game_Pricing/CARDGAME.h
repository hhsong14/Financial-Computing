#ifndef CARDGAME_H
#define CARDGAME_H
#include <iostream>
#include <algorithm>
using namespace std;

class card_game
{
	int a;
	float** memo;

	// initialize the memoization array, fill with zero
	void initialize(int size)
	{
		a = size/2 + 1;
		memo = new float*[a];

		for (int i = 0; i < a; i++)
			memo[i] = new float[a];

		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < a; j++)
			{
				memo[i][j] = 0;
			}
		}
	}

	// calculate the value of the game
	float value(int r, int b)
	{
		if (r == 0) // when no red cards left, value is b
			return ((float)b);
		else if (0 == b) // when no black cards left, value is 0
			return 0;
		else if (memo[r][b] != 0) // check if the value has already been calculated before
			return memo[r][b];
		else
		{
			float temp = ((float)r/(r+b)) * value(r-1, b) + ((float)b / (r+b)) * value(r, b-1);
			memo[r][b] = max((temp), (float)(b-r));
			return memo[r][b];
		}
	}

public:
	void game(int n)
	{
		initialize(n);
		cout << "Total Number of Cards = " << n << endl;
		cout << "Value of the game = " << value(n/2, n/2) << endl;
	}

};
#endif 
