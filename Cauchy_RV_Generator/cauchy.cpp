#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <random>
#include <chrono>

using namespace std;

#define STANDARD_CAUCHY_DENSITY(x) 1/(3.141592654*(1+(x*x)))
#define UNIT_NORMAL_DENSITY(x) exp(-x*x/2) / sqrt(2*3.141592654)

unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator (seed);

//default_random_engine generator (10);

double get_cauchy()
{
    cauchy_distribution <double> distribution(0.0,1.0);
    return (distribution(generator));
}

int main(int argc, char* argv[])
{
    double y;
    int no_of_trials, count[100];
    double total = 0.0;

    sscanf(argv[1], "%d", &no_of_trials);
    ofstream outf(argv[2]);

    cout << "Standard Cauchy RV Generator" << endl;
    cout << "#Trials = " << no_of_trials << endl;
    cout << "Output File = " << argv[2] << endl;

    for (int i = 0; i < 100; i++)
    {
        count[i] = 0;
    }
    
    for (int i = 0; i < no_of_trials; i++)
    {
        y = get_cauchy();
        total = total + y;
        for (int j = 0; j < 100; j++)
        {
            if ((y>= ((double) (j-51)/10)) && (y< ((double) (j-50)/10)))
                count[j]++;
        }
        
    }
    
    for (int j = 0; j < 100; j++)
    {
        outf << ((double) (j-50)/10) << ", " << ((double) count[j]/no_of_trials) <<
        ", " << (0.1*STANDARD_CAUCHY_DENSITY((double) (j-50)/10)) << endl;
    }
    

    cout << "Mean of " << no_of_trials << "-many Cauchy RVs = " <<  total / ((double) no_of_trials) << endl;
}
