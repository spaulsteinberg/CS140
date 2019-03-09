#include <iostream>
using namespace std;
/* 
Author: Samuel Steinberg
Date: August 31st, 2017

This program reads in a stream of inputs from stdin and computes the sum, min input, max input
 and counts the number of times the number of numbers entered by user
*/
int main()
{
	//Initialization of min, max, sum, and counter
	int min=0, max=0; 
	int sum=0;
	int counter=0;
	int inputted_nums; // represents the input stream
/*
	Sum, count, max, and min are calculated for each value entered by user.
	max and min are compared  after the first loop since the first entered number will be both min and max
 */
while(cin >>  inputted_nums)
	{
		sum=sum+inputted_nums;
		counter++;
		if (counter==1)
		{
			max=inputted_nums;
			min=inputted_nums;
		}
		if (inputted_nums > max){
			max=inputted_nums;
		}
			if (inputted_nums < min)
			{
				min=inputted_nums;
			}
	};

//Print the desired outputs
	cout << "Count: " <<  counter << endl;
	cout << "Sum " <<  sum << endl;
	cout << "Max: " <<  max << endl;
	cout << "Min: " <<  min << endl;
	
}
