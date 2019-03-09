/*
	Author: Sam Steinberg
	Date: October 27th, 2017
 */

#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

bool isprime(int n)
{
	// Result will store the remainder of the users number divided by the loop iteration
	// c is for the number of iterations
	int result;
	int c = sqrt(n);
	//if checks to see if the number is less than 2, else checks to get rid of those divisible by 2
	if (n < 2)
		return false;
//	else
//		if ( n % 2 == 0)
//			return false;
	//the if statement checks to see if the remainder is zero for each iteration of the for loop
	for (int i = 2; i <= c; i++)
	{
		result = n % i;
		if (result == 0)
		{
			return false;
		}
		
	}
	//if non of these conditions are met, the number is prime and will return true
		return true;
	
}
int main()
{
//user can stream in as many numbers as they want before they ctrl-d, if the number is
//prime (checked by calling the isprime(int) function, then it will trigger the cout statement
int number;
while(cin >> number)
if (isprime(number) == true)
{
	cout << number << " is a prime number" << endl;
}
}
