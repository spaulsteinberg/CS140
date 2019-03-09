/*
 *Author: Samuel Steinberg
  Date: September 7th, 2017
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <fstream>
using namespace std;

//Definitions of encode and decode, each taking in a string passed by reference and an integer with the purpose of offsetting the letters in the string
void encode(string&, int);
void decode(string&, int);

int main(int argc, char* argv[])
{
	// There must be three arguments: the executable, an encode/decode, and an offset
	if (argc !=3)
	{
		cerr << "Usage: Must enter 3 arguments " << endl;
		return 0;
	}
	// Second argument must be an offset between 0 and 9
	if ( (atoi(argv[2]) < 0) || (atoi(argv[2]) > 9) )
	{
		cerr << "Usage: Must enter a number between 0 and 9.  " << endl;
		return 0;
	}
	// first argument must either encode or decode
	if ( (strcmp(argv[1], "-encode")!=0) && ( (strcmp(argv[1], "-decode" )!=0)))
			{
				cerr << "Usage: Must enter either -encode or -decode. " << endl;
				return 0;
			}

	/* getline takes the input and new string and grabs the line of text
	 *must use strcmp to compare the values the first arguments and determine whether to use encode or decode
	 */
	string new_string;
	getline(cin, new_string);
	if ((strcmp(argv[1], "-encode") == 0))
	{
		 encode(new_string, atoi(argv[2]));
	}
	if ((strcmp(argv[1], "-decode") == 0))
	{
		decode(new_string, atoi(argv[2]));
	}
	cout << new_string << endl;

}

//encode takes in the string inputted by user and an offset for the number of letters moved to encode the string
void encode (string& user_input , int offset)
{
	
	int length_of_input = 0; //Initialization of C-style string component counter 


	/* loop runs on condition that the string character is true at each element
	 first if statement finds if it is lower case and adds the offset the user specifies 
	 second if statement loops the alphabet around by taking the resultant string value and subtracting the length of the alphabet to get the remainder
	 */
	while (user_input[length_of_input] != '\0')
	{
		if (islower(user_input[length_of_input]))
		{
			user_input[length_of_input] = user_input[length_of_input] +  offset;

		
			if (!(islower(user_input[length_of_input])))
			{
				user_input[length_of_input] = user_input[length_of_input] - 26;
			}
		}

		// Same loops as above, but for uppercase letters
		if (isupper(user_input[length_of_input]))
				{
					user_input[length_of_input] = user_input[length_of_input] + offset;

					if (!(isupper(user_input[length_of_input])))
					{
						user_input[length_of_input] = user_input[length_of_input] - 26;
					}
				}
				//Iterates through string by 1
		length_of_input++;
	}
}

// decode takes in the string inputted by the user and uses the offset to decode the string
void decode (string& user_input, int offset)
{
	int length_of_input = 0; // Initialization of C-style string counter

	/* loop runs on condition that the string character at position length_of_input is valid
	 first if statement finds if it is lower case and adds the specified offset
	 second if statement loops the alphabet around by adding the resultant value and offset, then adding by the length of the alphabet to get the decoded letter
	 counter then moves to the next position of the string
	 */
	while (user_input[length_of_input] != '\0')
	{
		if (islower(user_input[length_of_input]))
				{
					user_input[length_of_input] = user_input[length_of_input] - offset;
					
					if (!( islower(user_input[length_of_input])))
					{
						user_input[length_of_input] = user_input[length_of_input] + 26;
					}
				}
		
		//Same loops as above, but for uppercase letters
		if (isupper(user_input[length_of_input]))
		{
			user_input[length_of_input] = user_input[length_of_input] - offset;

			if (!( isupper(user_input[length_of_input])))
			{
				user_input[length_of_input] = user_input[length_of_input] + 26;
			}
		}
		//Iterates through string by 1
		length_of_input++;
	}
}
