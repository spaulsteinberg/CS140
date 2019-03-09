/*
Author: Sam Steinberg
Date: October 4th, 2017
*/
#include <iomanip>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

class isprime {
  public:
    isprime() {L.push_back(2);}
    bool operator()(int);
	bool prime(int);
	void print(vector<int>);
	void extract_prime(vector<int>, vector<bool>, vector<int>&);
  private:
    vector<int> L;
	void expanded_list(int);


};
//function uses a for loop checking the numbers less than the square root to see if it is divisible and therefore a factor --> not prime
bool isprime::prime(int num)
{
	int result;
	int c = sqrt(num);
	if (num < 2)
		return false;
	else
		if ((num%2) == 0)
			return false;
	for (int i = 2; i <=c; i++)
	{
		result = num % i;
		if (result == 0)
			return false;
	}
	return true; //true if not a factor
}
// List expands until n is greater than the last element and then checks if that is prime. If so, the number is addded to the list
void isprime::expanded_list(int n)
{
	for (int j = L.back() + 1; n > L.back(); j++)
	{
		if (prime(j))
		{
			L.push_back(j);
		}
	}
}
/*Overloads function operator, checks to see if the number is greater than the last element and expands the 
	list if true. Binary search returns 1 when number is found in list
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
//Creates random numbers between 1-100
int random_number()
{
	return rand()%100+1;
}
/*
	extract_prime takes a random number vector and bool vector. It runs through each element in the vector and when the 
	number is prime the bool vector will become true, which means it must be added to the new prime number array through push_back
 */
void extract_prime(vector<int> numbers, vector<bool> v2, vector<int>&prime_storage)
{
	for (int i = 0; i < numbers.size(); i++)
	{
		if (v2[i] == true)
		{
			prime_storage.push_back(numbers[i]);
		}
	}
}
/*Runs through the size of the prime number vector and sets the width with setw, offsets it to the right,
	uses the if statement to set the number of elements per line to 10, the vector must be output outside 
	of the for loop so it does not only print every 10th element
  */
void print(vector<int> v3)
{
	for (int i = 0; i < v3.size(); i++)
		{
			if ((i%10) == 0)
			{
				cout << endl;
			}
				cout << setw(4) << right << v3[i];
		}
	
}

int main(int argc, char *argv[])
{
	
	int N;
	isprime is;
	if (argc != 2) // if there is no second argument the size will be set to 10
		N=10;
	else
	if (atoi(argv[1]) > 0) // if there is no second argument the size will be set to 10
		N=atoi(argv[1]);

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
	//this vector will hold the prime numbers extracted by the extract_prime function, called below it by checking the int/bool vectors
	vector<int >prime_saver;
	extract_prime(myvec, v, prime_saver);

	cout << "All numbers in order of appearance: " << endl;
	//prints prime number vector in order they appeared
	print(prime_saver);
	//sort function sorts from least to greatest, iterating from beginning to end
	sort(prime_saver.begin(), prime_saver.end());
	//erase will delete numbers placated by unique by cutting them off after the iterator runs
	prime_saver.erase(unique(prime_saver.begin(), prime_saver.end()), prime_saver.end());
	cout << endl;
	cout << "Unique values in numerical order: " << endl;
	//Prints numerical primes
	print(prime_saver);
	cout << endl;
}
