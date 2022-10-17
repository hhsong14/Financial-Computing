#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class stable_marriage_instance
{
    // Private
    int no_of_couples;
    vector <vector <int> > Preference_of_men;
    vector <vector <int> > Preference_of_women;
    vector <int> match_for_men;
    vector <int> match_for_women;
    
    // private member function: checks if anybody is free in boolean "my_array"
    // returns the index of the first-person who is free in "my_array"
    // if no one is free it returns a -1.
    int anybody_free(vector <bool> my_array)
    {
        // fill the necessary code for this function
        for (int i = 0; i < my_array.size(); i++)
        {
            if (my_array[i] == true)
                return i;
        }
        return -1;
    }
    
    // private member function: if index1 is ranked higher than index2
    // in a preference array called "my_array" it returns "true"; otherwise
    // it returns "false"
    bool rank_check (vector <int> my_array, int index1, int index2)
    {
        // fill the necessary code for this function
        bool result = true;
        for (int i = 0; i < my_array.size(); i++)
        {
            if (my_array[i] == index1)
            {
                break;
            }

            if (my_array[i] == index2)
            {
                result = false;
                break;
            }
        }
        return result;
    }
    
    // private member function: implements the Gale-Shapley algorithm
    void Gale_Shapley()
    {
        vector <bool> is_man_free;
        vector <bool> is_woman_free;
        vector <vector <bool> > has_this_man_proposed_to_this_woman;
        
        int man_index, woman_index;
        
        // initializing everything
        for (int i= 0; i < no_of_couples; i++)
        {
            // do the necessary initialization here
            vector <bool> temp;
            
            is_man_free.push_back(true);
            is_woman_free.push_back(true);
            match_for_men.push_back(-1);
            match_for_women.push_back(-1);
            has_this_man_proposed_to_this_woman.push_back(temp);
        }

        for (int i = 0; i < no_of_couples; i++)
        {
            for (int j = 0; j < no_of_couples; j++)
                has_this_man_proposed_to_this_woman[i].push_back(false);
        }

        // Gale-Shapley Algorithm
        while ( (man_index = anybody_free(is_man_free)) >= 0)
        {
            // fill the necessary code here
            for (int i = 0; i < no_of_couples; i++) // find the first woman on the man's preference list that has not been proposed
            {
                woman_index = Preference_of_men[man_index][i];
                if (has_this_man_proposed_to_this_woman[man_index][woman_index] == false)
                    break;
            }

            if (is_woman_free[woman_index] == true) // the woman is un-engaged
            {
                match_for_men[man_index] = woman_index;
                match_for_women[woman_index] = man_index;
                is_man_free[man_index] = false;
                is_woman_free[woman_index] = false;
                has_this_man_proposed_to_this_woman[man_index][woman_index] = true;
            }
            else
            {
                int current_match = match_for_women[woman_index]; // find the current match of the woman
                if (rank_check(Preference_of_women[woman_index], man_index, current_match)) // change engagement, accept the man
                {
                    match_for_women[woman_index] = man_index;
                    match_for_men[man_index] = woman_index;
                    match_for_men[current_match] = -1;
                    is_man_free[man_index] = false;
                    is_man_free[current_match] = true;
                    has_this_man_proposed_to_this_woman[man_index][woman_index] = true;
                }
                else // reject the man
                {
                    has_this_man_proposed_to_this_woman[man_index][woman_index] = true;
                }
            }


        }
    }
    
    // private member function: reads data
    void read_data(int argc, const char * argv[])
    {
        // fill the necessary code here.  The first entry in the input
        // file is the #couples, followed by the preferences of the men
        // and preferences of the women.  Keep in mind all indices start
        // from 0.
        ifstream input_file(argv[1]);
        if (input_file.is_open())
        {
            input_file >> no_of_couples;
            for (int i = 0; i < no_of_couples; i++)
            {
                vector <int> temp;
                Preference_of_men.push_back(temp);
                Preference_of_women.push_back(temp);
            }
            
            for (int i = 0; i < no_of_couples; i++)
            {
                for (int j = 0; j < no_of_couples; j++)
                {
                    int value;
                    input_file >> value;
                    Preference_of_men[i].push_back(value);
                }
            }
            
            for (int i = 0; i < no_of_couples; i++)
            {
                for (int j = 0; j < no_of_couples; j++)
                {
                    int value;
                    input_file >> value;
                    Preference_of_women[i].push_back(value);
                }
            }

            cout << "Gale-Shapley Algorithm" << endl << "Input File Name: " << argv[1] << endl;
            cout << "Number of Couples = " << no_of_couples << endl;
            cout << endl;
            cout << "Preferences of Men" << endl;
            cout << "------------------";
            for (int i = 0; i < no_of_couples; i++)
            {
                cout << endl << "(" << i << "): " ;
                for (int j = 0; j < no_of_couples; j++)
                    cout << Preference_of_men[i][j] << " ";
            }
            cout << endl << endl;

            cout << "Preferences of Women" << endl;
            cout << "--------------------";
            for (int i = 0; i < no_of_couples; i++)
            {
                cout << endl << "(" << i << "): " ;
                for (int j = 0; j < no_of_couples; j++)
                    cout << Preference_of_women[i][j] << " ";
            }
            cout << endl << endl;
        } 
        else 
        {
            cout << "Input file does not exist" << endl;
        }
        
    }
    
    // private member function: print solution
    void print_soln()
    {
        // write the appropriate code here
        cout << "Matching for Men" << endl;
        for (int i = 0; i < no_of_couples; i++)
        {
            cout << "Man: " << i << " -> Woman: "<< match_for_men[i] << endl;
        }
        cout << endl;
        
        cout << "Matching for Women" << endl;
        for (int i = 0; i < no_of_couples; i++)
        {
            cout << "Woman: " << i << " -> Man: "<< match_for_women[i] << endl;
        }
        cout << endl;
    }
    
public:
    void solve_it(int argc, const char * argv[])
    {
        read_data(argc, argv);

        Gale_Shapley();

        print_soln();
    }
};

int main(int argc, const char * argv[])
{
    stable_marriage_instance x;
    x.solve_it(argc, argv);
}

