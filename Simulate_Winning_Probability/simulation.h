
#ifndef ALICE_AND_BOB
#define ALICE_AND_BOB

#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

class game
{
private:
	double alice_probability, bob_probability;
    int no_of_trial;

    int combination(int n, int i)
	{
		if (i == 0)
			return 1;
		else if (i == 1)
            return n;
		else
            return combination(n, i - 1)*(n - i + 1) / i;
	}

	
    double theoretical_prob(double q, double p, int n)
	{
		// implement equation 1.1
		double prob = 0;
		for (int r = 0; r < n; r++)
		{
			for (int s = r + 1; s <= n; s++)
			{
				prob = prob + combination(n, r)*pow(p, r)*pow(1 - p, n - r)*combination(n, s)*pow(q, s)*pow(1 - q, n - s);
			}
		}
		return prob;
	}

    float get_uniform()
    {
        return ((float) rand()/RAND_MAX);
        //return (((float) random())/(pow(2.0, 31.0)-1.0));
    }

    double simulation_prob(int number_of_toss)
    {
        int alice_win = 0;
        for (int i=0; i<no_of_trial; i++)
        {
            int heads_for_alice = 0;
            int heads_for_bob = 0;
            for (int j=0; j< number_of_toss; j++)
            {
                if (get_uniform() < alice_probability)
                    heads_for_alice++;
                if (get_uniform() < bob_probability)
                    heads_for_bob++;
            }

            if (heads_for_alice > heads_for_bob)
                alice_win++;
        }

        return ((double) alice_win) / ((double) no_of_trial);
    }

public:
    vector <double> simulated_data;
    vector <double> theoretical_data;

    void set(double alice, double bob, int trials)
    {
        alice_probability = alice;
        bob_probability = bob;
        no_of_trial = trials;
    }

    int find_optimal()
    {
        int n = 1;
        double p1 = theoretical_prob(alice_probability, bob_probability, n);
        double p2 = theoretical_prob(alice_probability, bob_probability, n+1);
        while (p2 > p1)
        {
            n++;
            p1 = theoretical_prob(alice_probability, bob_probability, n);
            p2 = theoretical_prob(alice_probability, bob_probability, n+1);
        }
        return n;
    }

    void create_data_file() 
    {
        for (int i = 0; i < 30; i++) {
            theoretical_data.push_back(theoretical_prob(alice_probability, bob_probability, i+1));
            simulated_data.push_back(simulation_prob(i+1)); 
        }
        
        ofstream outf("data.csv");
        
        for (int i = 0; i < simulated_data.size(); i++) {
            outf << i+1 << ", " << simulated_data[i] << ", " << theoretical_data[i] << endl;
        }
    }
    

};
#endif

