/*
	Author: Samuel Steinberg
	Date: September 14th, 2017 
*/
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

const string face[] = { "Ace", "2", "3", "4", "5", "6", "7",
                        "8", "9", "10", "Jack", "Queen", "King" }; 
const string suit[] = { "Clubs", "Diamonds", "Hearts", "Spades" };

string random_card(bool verbose=false) {
	string card;

	card = face[ rand()%13 ];
	card += " of ";
	card += suit[ rand()%4 ];

	if (verbose)
	  cout << card << "\n";

	return card;
}

int main(int argc, char *argv[])
{
	bool verbose = false;
	int seedvalue = 0;

	for (int i=1; i<argc; i++) {
	  string option = argv[i];
	  if (option.compare(0,6,"-seed=") == 0) {
	    seedvalue = atoi(&argv[i][6]);
	  } else if (option.compare("-verbose") == 0) {
	    verbose = true;
	  } else 
	    cout << "option " << argv[i] << " ignored\n";
	}

	srand(seedvalue); 
	int deck[4][13] = {0};    //Deck is  a 4-row, 13-column 2D array all initialized to 0

	// declare a table called deck that keeps track of
	// card faces dealt for each suit -- initialize to 0
	
	bool done = false; //while loop condition: checks to see if terminating condition has been met
	int n = 0; // variable to note what suit program ended

	//while loop checks to see if the terminating condion has been met
	//stringstream takes the card and separates it into the suit and face along with the "of" which is noted as garbage
	//face2 and suit2 created as references to face and suit
	//nested for loop goes through 2D array and adds to it when the card comes up by adding to the deck at the specific element
	while (!(done)) {
	  string card = random_card(verbose);
	  string garbage= "of";
	  stringstream ss;
	  ss.str(card);

	  string face2, suit2;
	  ss >> face2 >> garbage >>  suit2;
	  
	// done = false;

	  for (int i=0; i < 4; i++)
	  {
		  for (int j=0; j< 13; j++)
		  {
			if ((suit2 == suit[i]) && (face2 == face[j]))
					{
						deck[i][j]++;
					}
					
		  }
	  }

	  //the if statements check to see if the terminating conditions have been met
	  //and if they have to set note the location of where it ended and sends the terminating command to the while condition
	  //through the break statement
			if (((deck[0][10]) > 0) && (( deck[0][11]) > 0) && (( deck[0][12]) > 0 ))
			{
				done = true;
				n = 0;
				break;
			}

			if (((deck[1][10]) > 0) && (( deck[1][11]) > 0) && (( deck[1][12]) > 0 ))
			{
				done = true;
				n = 1;
				break;
			}

			if (((deck[2][10]) > 0) && (( deck[2][11]) > 0) && (( deck[2][12]) > 0 ))
			{
				done = true;
				n = 2;
				break;
			}
		  
			if (((deck[3][10]) > 0) && (( deck[3][11]) > 0) && (( deck[3][12]) > 0 ))
			{
				done = true;
				n = 3;
				break;
			}
	  
	  // reverse engineer card suit and face

      // break out of loop if stopping criteria met
	}
	//Output setting the correct spacing by using setw and setting these spaces right of the statement
	//suit[i] sets the suit names on the far left, second for loop outputs  the actual result of the 2D array/program
	for (int i=0; i < 4; i++)
	{
		cout << setw(8) << right << suit[i] <<  " :";
		for (int j=0; j < 13; j++)
				{
					cout << setw(4) << right << deck[i][j];
				}
		
		// checks the suit index where the terminating conditions were met and outputs a "**" at the end of the array row (i index)
		if (n == i)
		{
			cout << "**";
		}
		//new line between each row
		cout << endl;
	
	}	// print formatted table contents to stdout 
}
