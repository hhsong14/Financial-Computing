#include <iostream>
#include "CARDGAME.h"

int main (int argc, char * const argv[]) 
{
    card_game x;
    
    int number_of_cards;
    sscanf (argv[1], "%d", &number_of_cards);
	
	x.game(number_of_cards);
	
    return 0;
}