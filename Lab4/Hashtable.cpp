/*
	Author: Samuel Steinberg
	Date: October 17th, 2017
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

typedef unsigned int uint;

class hash_table
{	//keyline is a structure that has a word to act as a key and a vector that stores lines numbers
	//inuse checks to see if the word has been used before and the op overload compares a string to a class object
	struct key_line
	{
		string key_word;
		vector<int> line_number;
		bool inuse();
		bool operator==(const string &);
	};

		int hash(const string &);
		int nextprime(int);
		int qprobe(const string &);
		void resize();

		int num_inuse;
		int max_inuse;

		vector<key_line> table;
		vector<int> empty;
	public:
		hash_table();
		void insert(const string &,const int&);
		const vector<int>& find(const string&);
};
//checks to see if the word is already in use, will return false if the string is empty
bool hash_table::key_line::inuse()
{
	if (key_word.empty())
		return false;
	
	return true;
}
//Comparison of passed string to key word from key_line class
bool hash_table::key_line::operator==(const string &word)
{
	if (word == key_word)
		return true;

	return false;
}
//find function returns the line number by probing for the key and adds it to the index, function then checks to see if the index is in use
//and will return the line number where it is being used...or else it will return an empty vector if not found
const vector<int>& hash_table::find(const string& key)
{
	int index = qprobe(key);
	
	if (table[index].inuse())
	{
		return table[index].line_number;
	}
	else
		return empty;
}
//Table assignments given by hashtable_2 handout
hash_table::hash_table()
{
	int N = 23;
	table.assign( N, key_line());

	num_inuse = 0;
	max_inuse = N/2;
}
/*Insert adds to the hashtable, if statement checks to see if the index is in use, and the iterator 
then scans the table line numbers from beginning to end with the target being the integer line_num
if it reaches the end of the vector, it will add the line num to the table
if not in use the key and line number will be added and the table resized through the member function call
*/
void hash_table::insert(const string &key, const  int& line_num)
{
	int index = qprobe(key);
	vector<int>::iterator iv;
	if (table[index].inuse())
	{
		iv= std::find(table[index].line_number.begin(), table[index].line_number.end(), line_num);

		if( iv == table[index].line_number.end())
		{
			table[index].line_number.push_back(line_num);
		}
	}
	else{
		table[index].key_word = key;
		table[index].line_number.push_back(line_num);
		if (++num_inuse >= max_inuse)
			resize();
}
}
//determines next prime number
int hash_table::nextprime(int N)
{
	int i = 2;
	while (i*i <= N)
	{
		if (N%i == 0)
		{
			N++;
			i=1;
		}
		i++;
	}
	return max(3,N);
}
//probes for the hash key, checks to see if the index is in use and that the table index is not the key
//This will then run to return the index
int hash_table::qprobe(const string &key)
{
	int index = hash(key);

	int k = 0;
	while (table[index].inuse() && !(table[index] == key))
	{
		index += 2*(++k) - 1;
		index = index % table.size();
	}
	return index;
}
//A vector of keylines is declared, this function then defines the size of the hash table by pushing back when index's
//are in use. Both for loops will be used for resizing and the table is assigned the keylines
void hash_table::resize()
{
	vector<key_line> tmp_table;
	for (int i=0; i<(int)table.size(); i++)
	{
		if (table[i].inuse())
			tmp_table.push_back(table[i]);
	}

	int N = nextprime(2*table.size());
	table.assign(N, key_line());

	num_inuse = 0;
	max_inuse = N/2;

	for (int i=0; i<(int)tmp_table.size(); i++)
	{
		key_line &key = tmp_table[i];
		table[ qprobe(key.key_word) ] = key;
		num_inuse++;
	}
}
//Hashes the string
int hash_table::hash(const string &key)
{
	int index = 0;
	const char *c = key.c_str();

	while (*c)
		index = ((index << 5) | (index >> 27)) + *c++;

	return (uint)index % table.size();
}
//checks each character to see if it is punctuation and if so will change the character to a blank space
char punct_to_blank(char c)
{
	if (ispunct(c))
	{
		c = ' ';
	}
	return c;
}
int main(int argc, char *argv[])
{	
	//Error checks to kill program when a second argument isnt given
	if (argc != 2)
	{
		cerr << "Usage: ./Hashtable textfile " << endl;
		return 0;
	}
	//input and output streams declared, will open the text file when prompted by user at argv[1]
	ifstream text_view;
	ofstream fout;
	text_view.open(argv[1]);
	stringstream ss;
	//Program killed if file fails to open
	if(text_view.fail())
	{
		cerr << "File failed to open!" << endl;
		return 0;
	}
	
	hash_table H;
	vector<string> cached; //Vector to store lines
	string line;
	string word; //Temporary variable to hold parsed words
	int i = 0;
/*When text file is open: getline will run until the text is extinguished, acquiring each line from the text file. These lines will then be 
pushed back onto the cached line vector. Tranform function will called the operation punct_to_blank to erase punctuation
when entering the hash table. The stringstream will then separate the lines by words and insert them into the table. 
An iterator is declared to keep track of the index. Stringstream is then cleared.
 */
	if(text_view.is_open())
	{
		while (getline(text_view, line))
		{
			cached.push_back(line);
			transform(line.begin(), line.end(), line.begin(), punct_to_blank);
			ss.str(line);

			while (ss >> word)
			{
				H.insert(word, i);
			}

			i++;
			ss.clear();
		}

	}
//File closed when end is reached
	fout.close();
	string key; //user input
	while (1)
	{	
		cout << "find>";
		cin >> key;
		if (cin.eof()) //allows user to stop on crtl-d
		{return 0;}
		const vector<int>& holder = H.find(key); //Temporary vector to hold found values
		for ( size_t j = 0; j < holder.size(); j++) // printing of the line number and text line by utulizing the cached data
		{
			cout << (holder[j]+1) << ": "  << cached[holder[j]] << endl;
		}
	}
}
