#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "simulation.h"
using namespace std;

int main (int argc, char * const argv[])
{
	game x;
	double alice_prob, bob_prob;
	int number_of_trials;
	sscanf (argv[1], "%d", &number_of_trials);
	sscanf (argv[2], "%lf", &alice_prob);
	sscanf (argv[3], "%lf", &bob_prob);

	cout << "Number of Trials = " << number_of_trials << endl;
	cout << "Probability of head up for Alice = " << alice_prob << endl;
	cout << "Probability of head up for Bob = " << bob_prob << endl;
    x.set(alice_prob, bob_prob, number_of_trials);
    
    cout << "The optimal number of coin tosses is " << x.find_optimal() << endl;
	x.create_data_file();
}