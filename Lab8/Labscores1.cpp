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

//Stores scores and its uses
class labscores_t
{
	public:
	labscores_t(){median = 0; mean = 0.0;}
	void add_data(int);
	void set_stats();
	void print_labscores() const; 
	private:
		vector<int> scores;
		int median;
		float mean; //go to one decimal place and used fixed
};

void labscores_t::add_data(int data)
{
	scores.push_back(data);
}
void labscores_t::set_stats()
{
	int score_total = accumulate(scores.begin(), scores.end(), 0);
	mean = ((score_total*1.0)/scores.size()*1.0);

	 sort(scores.begin(), scores.end());

	size_t num_elements = scores.size();

	median = scores[(num_elements-1)/2];

}
void labscores_t::print_labscores() const
{
	for (int i = 0; i < scores.size(); i++)
	{
		cout << right << " " << scores[i];
	}
	cout << " : " <<  median << " " << fixed << setprecision(1) << mean;
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
void name_t::setFirst(string f)
{
	first = f;
}
void name_t::setLast(string l)
{
	last = l;
}
string name_t::getFirst()
{
	return first;
}
string name_t::getLast()
{
	return last;
}
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
void name_t::print_name(int length) const
{
	cout << setw(length) << setfill('.') << left << (last + ", " + first + " ");  //Sets field found in main, filling w/0's and putting name over
}
/*
typedef map<name_t, labscores_t> map_t;
typedef map_t::iterator map_iterator_t;
class heap_t
{
	public:
		heap_t();
		bool empty() const;
		void add_data(const map_iterator_t &); //push back iterator into vector
		void heapify(); //call make_heap, pass in beginning and end iterators
	    map_iterator_t extract_top();//save front(), call pop_heap, then call pop_back to remove last vector element BOTTOM of heap handout
	private:
		struct data_t
		{
			bool operator<(const data_t &);
			map_iterator_t it;			
		};

		vector<data_t> data;
};

heap_t::heap_t()
{
	;
}
bool heap_t::empty() const
{
	if (data.empty())
	{
		return true;   //No data in vector
	}
	return false;
}
void heap_t::add_data(const map_iterator_t &m)
{
	data.push_back(m);
}
void heap_t::heapify()
{
	make_heap(data.begin(), data.end());
}
map_iterator_t heap_t::extract_top()
{
		map_iterator_t map_it;

		map_it = data.front().it;  //max heap element from its front, iterator of data_t
		pop_heap(data.begin(), data.end()); //pops the front element
		data.pop_back(); //delete the last element which is complete and utter trash

		return map_it;
}
bool heap_t::data_t::operator<(const data_t& din)
{
	int flag1 = 0, flag2 = 0;
	if (it->second.mean < din->it->second.mean)
	{
		flag1 = 1;
		return true; //true denotes passed data has a greater mean
	}
	else
		if (it->second.mean == din->it->second.mean)
			if (it->second.median < din->it->second.median)
			{
				flag2 = 1;
				return true; //true when passed data has greater median with same mean
			}
	else
		if (flag1 == 1 && flag2 == 1)
		{
			//compare names
		}
}
*/
typedef map <name_t, labscores_t> map_t;
typedef map_t::iterator map_iterator_t;
int main (int argc, char*argv[])
{

	string first, last, student_data; //first and last to store names and student_data for the whole line
	int max = 0;
	int scores; //variable to hold student scores
	ifstream fin;
	ofstream fout;

	if (argc !=3)
	{
		cerr << "Usage: Not enough arguments." << endl;
	}
/*
	if (argv[1] != "-byname" && argv[1] != "-byrank" && argv[1] != "-topten")
	{
		cerr << "Usage: labscores -byname|byrank|top10 datafile.txt";
	}
*/	
	fin.open(argv[2]);
	
	if (fin.fail())
	{
		cerr << "File failed to open." << endl;
	}

	map_t m;
	map_iterator_t it;
	stringstream ss;
	name_t n;
	
	if (string(argv[1]) == "-byname")   //make || for the other two, then make an else for the above usage error
	{
		while (getline(fin, student_data))
		{
			labscores_t l;
			ss.str(student_data);

			ss >> first >> last;
			
			
			string full_name = first + ", " + last;
			if (max < full_name.length())
			{
				max = full_name.length();
			}

			n.setFirst(first);
			n.setLast(last);
			
			while (ss >> scores)
			{
				l.add_data(scores);
			}

			l.set_stats();

			m.insert( make_pair(n,l));
			
			ss.clear();
		}


	for (it = m.begin(); it != m.end(); it++)
	{
		it -> first.print_name(max+3);
		it -> second.print_labscores();
		cout << endl;
	}
		
	}
	fout.close();

}

