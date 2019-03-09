/*
	Author: Sam Steinberg
	Date: OCtober 3rd, 2017
*/
#include <iostream>
#include <algorithm>
#include <list>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

class isprime {
  public:
    isprime() {L.push_back(2);} 
    bool operator()(int);
	bool prime(int);
  private:
    vector<int> L;
	void expanded_list(int);
};
/* checks for prime numbers by checking numbers greater than 2 and also excludes all even numbers before
  the search, where a square root is taken and then a remainder is searched for all the lesser numbers,
  returns a bool true if prime, and false if not
 */
bool isprime::prime(int num)
{
	int result;
	int c = sqrt(num);
	if (num < 2)
		return false;
	else
		if ((num % 2) == 0)
			return false;

	for ( int i = 2; i <= c; i++)
	{
		result = num % i;
		if (result == 0)
			return false;
	}
	return true;
}
/* expands list when an inputted number is greater than the back of the list and the 
if statement calls the prime function to check if its a prime number, and if true will be added to the list
*/
void isprime:: expanded_list(int n)
{

	for (int j = L.back() + 1; n > L.back(); j++)
	{
		if (prime(j))
		{
			L.push_back(j);
		}
	}

}
/* If statement checks to see if the inputted number is greater than the back element,
 and if true will call the expanded_list function to add the number to the list. 
 A variable is then made to store the result of the binary search and returns that variable
 */

bool isprime::operator()(int number)
{
    if (L.back() < number)
	{
		expanded_list(number);
	}

	int result = binary_search(L.begin(), L.end(), number);
	return result;
}
//Returns random numbers between 1-100
int random_number()
{
	return rand()%100+1;
}

int main(int argc, char *argv[])
{
	int N;

	isprime is;
	if (atoi(argv[1]) > 0)  // finds integer value of second argument and sets the size equal to it
		N = atoi(argv[1]);
	if (argc != 2) // if there is no second argument the size will be set to 10
		N=10;

	srand(N); // N as a seed to generate the random numbers

	// integer vector to hold the values generated, boolean vector to hold overloaded function call result
	vector<int> myvec(N);
	vector<bool> v(N); 
	//Generates random number vector
	generate(myvec.begin(), myvec.end(), random_number);
	//Applies the function to the elements of the two vector sequences
	transform(myvec.begin(), myvec.end(), v.begin(), is );
	//c counts where the overloaded function returned true, meaning where it was prime
	int c = count(v.begin(), v.end(),true);
	
	cout << "Sequence contains " << c << " prime numbers." << endl;

}
