#include <iostream>

/*
 Author: Samuel Steinberg
 Date: August 31st, 2017

 This program prompts the user to take random values given from stdin and calculates
 and prints the sum, min, max and number of values given and integrates the use of classes
 to perform a certain task
 */

using namespace std;
/*
 class stats uses a constructor to initialize the statistics the program calculates
 and contains the function definitions 
 */class stats
{
	int min, max, sum, counter;
 public:
	stats()
	{
		min=0;
		max=0;
		counter=0;
		sum=0;
	}
	 void push(int);
	 void print();
};
/*
	Instance variable of class stats initialized tothe constructor stats()
	Then utulizes a loop to allow itself to be generic and take in as much data 
	as the user wants to input
 */
int main()
{
	int input;
	stats s= stats();
while(cin >> input)
	{
		s.push(input);
	};

	s.print();
}
/*
	push function of class stats  utulizing if statements to compare the given inputs and find the min and max.
	The first input is set as the min and max in the first loop to give further comparisons a base of comparison
 */
void stats:: push(int inputted_nums){
		sum=sum+inputted_nums;
		counter++;
		if (counter==1)
		{
			max= inputted_nums;
			min= inputted_nums;
		}
			if (inputted_nums > max)
			{
				max=inputted_nums;
			}
			if (inputted_nums < min)
			{
				min=inputted_nums;
			}
		}
/*
 print function of class stats which returns the output. This is run after the loop in main
 calculating the statistics so the output consists of the final and correct data
 */
void stats:: print(){

  cout << "Count: " <<  counter << endl;
  cout << "Sum: " << sum << endl;
  cout << "Max: " <<  max <<endl;
  cout << "Min: " <<  min << endl;
	
}
