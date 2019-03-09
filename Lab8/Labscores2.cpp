/*
	Author: Samuel Steinberg
	Date: November 29th, 2017
*/
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ostream>
#include <iomanip>
#include <map>
#include <utility>
#include <numeric>
#include <string>
#include <istream>
#include <fstream>

using namespace std;

//Stores scores and its uses, get functions to give heap access when pointed at
class labscores_t
{
	public:
	labscores_t(){median = 0; mean = 0.0;}
	void add_data(int);
	void set_stats();
	void print_labscores() const;
	int getMedian() {return median;}
	float getMean() {return mean;}
	private:
		vector<int> scores;
		int median;
		float mean; //go to one decimal place and used fixed
};
//adds labscores to the vector of scores
void labscores_t::add_data(int data)
{
	scores.push_back(data);
}
//gets total scores for each student using accumulate, sort sorts the scores, using these i calculated the median and mean
void labscores_t::set_stats()
{
	int score_total = accumulate(scores.begin(), scores.end(), 0);
	mean = ((score_total*1.0)/scores.size()*1.0);

	 sort(scores.begin(), scores.end());

	size_t num_elements = scores.size();

	median = scores[(num_elements-1)/2];

}
//Output of lab scores, setfill used to set spacing in field, set to one decimal point for scores w/set precision
void labscores_t::print_labscores() const
{
	for (unsigned int i = 0; i < scores.size(); i++)
	{
		cout << " " << setfill(' ') << right << setw(2) << scores[i];
	}
	cout << " : " << setw(2) <<  median << " " << fixed << setprecision(1) << mean;
}

//Stores names and its uses
class name_t
{
	public:
		name_t(const string& f, const string& l){first=f;last=l;}
		name_t() {;}
		bool operator<(const name_t&) const;
		void print_name(int length) const;
		void setFirst(string);
		void setLast(string);
		string getFirst();
		string getLast();
	private:
		string first;
		string last;


};
//sets first name when class called
void name_t::setFirst(string f)
{
	first = f;
}
//sets last name when class called
void name_t::setLast(string l)
{
	last = l;
}
//getter function--unused
string name_t::getFirst()
{
	return first;
}
//getter function-- unused
string name_t::getLast()
{
	return last;
}
//set string comparision to passed in name and is compared to the string in the class
bool name_t::operator<(const name_t& rhs) const
{
	string s = last + ", " + first;
	string t = rhs.last + ", " + rhs.first;
	if ( string(s) < string(t) )
	{
		return true; //true if passed f/l is less than compared 
	}
	return false; //false if passed f/l is greater or equal to compared
}
//stl setfill used when setting the field and puts in ellipses...left justified and name outputted
void name_t::print_name(int length) const
{
	cout << setw(length) << setfill('.') << left << (last + ", " + first + " ");
}

typedef map<name_t, labscores_t> map_t;
typedef map_t::iterator map_iterator_t;
//heap class and its members
class heap_t
{
	public:
		heap_t();
		bool empty() const;
		void add_data(const map_iterator_t &); //push back iterator into vector
		void heapify(); //call make_heap, pass in beginning and end iterators
	    map_iterator_t extract_top();//save front(), call pop_heap, then call pop_back to remove last vector element
	private:
		struct data_t
		{
			bool operator<(const data_t&);
			map_iterator_t it;			
		};

		vector<data_t> data;
};
//Doesnt need anything in constructor
heap_t::heap_t()
{
	;
}
//empty when data vector of objects is empty
bool heap_t::empty() const
{
	if (data.empty())
	{
		return true;   //No data in vector
	}
	return false;
}
//instance of data object, set its iterator equal to the passed map iterator, then push d onto vector of data objects
void heap_t::add_data(const map_iterator_t &m)
{
	data_t d;
	d.it = m;
	data.push_back(d);
}
//use stl make_heap to make the heap starting from the beginning to end of the data vector
void heap_t::heapify()
{
	make_heap(data.begin(), data.end());
}
//Extracts top element, see below comments
map_iterator_t heap_t::extract_top()
{
		map_iterator_t map_it;

		map_it = data.front().it;  //max heap element from its front, iterator of data_t
		pop_heap(data.begin(), data.end()); //pops the front element
		data.pop_back(); //delete the last element which is complete and utter trash

		return map_it;
}
typedef map<name_t, labscores_t> map_t;
typedef map_t::iterator map_iterator_t;
//pointer from iterator in struct points to both the passed data object and the object in class
//Really after that just simple comparisions between passed obect and data iterator
bool heap_t::data_t::operator<(const data_t& rhs)
{
	if (it->second.getMean() < rhs.it->second.getMean())
	{
		return true; //true denotes passed data has a greater mean
	}

	if (it->second.getMean() == rhs.it->second.getMean())
		if (it->second.getMedian() < rhs.it->second.getMedian())
		{
			return true; //true when passed data has greater median with same mean
		}
	if ((it->second.getMean() == rhs.it->second.getMean()) && (it->second.getMedian() == rhs.it->second.getMedian()))
	{
		if (rhs.it->first < it->first)
		{
			return true; //true denotes passed data has lesser name value
		}
	}	
	return false;
}

typedef map <name_t, labscores_t> map_t;
typedef map_t::iterator map_iterator_t;
int main (int argc, char*argv[])
{

	string first, last, student_data; //first and last to store names and student_data for the whole line
	unsigned int max = 0; //holds max length of field
	int scores; //variable to hold student scores
	ifstream fin;
	ofstream fout;
	//Check for number of arguments
	if (argc !=3)
	{	
		cerr << "Usage: labscores -byname|byrank|top10 datafile.txt";
	}
	//Check for correct 1st argument
	if (string(argv[1]) != "-byname" && string(argv[1]) != "-byrank" && string(argv[1]) != "-top10")
	{
		cerr << "Usage: labscores -byname|byrank|top10 datafile.txt";
	}
	
	fin.open(argv[2]);
	//Will not open with file it does not have access to, thereby taking care of 3rd arg
	if (fin.fail())
	{
		cerr << "File failed to open." << endl;
	}

	map_t m;
	map_iterator_t it;
	stringstream ss;
	name_t n;
	heap_t h;
	//Reads in each line and parses data
		while (getline(fin, student_data))
		{
			labscores_t l;
			ss.str(student_data);

			ss >> first >> last;
			
			//This chunk calculates the max length the field can be
			string full_name = first + ", " + last;
			if (max < full_name.length())
			{
				max = full_name.length();
			}
			
			//Setting of the names in class name_t
			n.setFirst(first);
			n.setLast(last);
			//Parsing of scores, then calls labscores_t add_data function to push it onto its vector
			while (ss >> scores)
			{
				l.add_data(scores);
			}
			//Calculates stats newly put on vector
			l.set_stats();
			//name and labscores inserted into map using make_pair
			m.insert( make_pair(n,l));
			
			ss.clear(); //Clears stringstream after each iteration of while loop
		}
	//Iterator traverses map, gets access to name_t and labscores_t and print functions
	if (string(argv[1]) == "-byname")
	{
		for (it = m.begin(); it != m.end(); it++)
		{
			it -> first.print_name(max+3);
			it -> second.print_labscores();
			cout << endl;
		}	
	}
	//Same traversal, added to heap_t vector
	if (string(argv[1]) == "-byrank")
	{
		for (it = m.begin(); it != m.end(); it++)
		{
			h.add_data(it);
		}
		h.heapify(); //heap created
		while (!h.empty()) //extracts the greatest rank of student for the entire heap function while it still has data (explanation of below)
		{
			it = h.extract_top();	
			it -> first.print_name(max+3);
			it -> second.print_labscores();
			cout << endl;
		}	
	}
	//Same as above, but counter starts at the first index and goes to the 9th. This will print the 10 greatest students
	if (string(argv[1]) == "-top10")
	{
		for (it = m.begin(); it != m.end(); it++)
		{
			h.add_data(it);
		}
		h.heapify();
		int counter = 0;
		while (counter < 10)
		{
			it = h.extract_top();	
			it -> first.print_name(max+3);
			it -> second.print_labscores();
			cout << endl;
			counter++;
		}	
	}


	fout.close(); //File is closed. Dunn. Peep Josh.

}

