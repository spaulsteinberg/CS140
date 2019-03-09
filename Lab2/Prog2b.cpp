/*
	Author: Samuel Steinberg
	Date: September 14th, 2017 
*/
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

// List class has struct as a member along with multiple functions that support the destructor and insert
class list 
{
	struct node
	{
		node () { data = 0; }
		int data;
		node *next;
	};
	public:
	
	list();
	~list();
	void erase(int);
	void clear();
	bool empty() const  {return N == 0;}
	void insert(int);
	private:
	int N;
	node *head;
	node *findnode(int);
	friend ostream & operator<<(ostream &, const list &);
};
// Constructor initializes head to node and the size of the list
list :: list()
{
	head = new node();
	N=0;
}
// Destructor deallocates/clears the memory the list had taken and deletes the head
list :: ~list()
{
	clear();
	delete head;
}
// erase function changes the pointers and deletes p, and changes the size of the list by decrementing N
void list::erase(int i)
{
	node *p;
	node *pp = findnode(i-1);
	p= pp -> next;
	pp->next = p->next;

	delete p;

	N--;
}
// clear deleted the first element of the list while it is not empty (deletes all elements but head)
void list::clear()
{
	while (!empty())
		erase(0);
}
// find node uses an index value to determine where in the list the node is and returns it
list::node *list::findnode(int i)
{
	if (i == -1)
	{
		return head;
	}
	node *p= head -> next;

	while (i--)
	{
		p = p -> next;
	}
	return p;
}
/*
 Insert declares two nodes and their positions (I set them to the head and the node after head)
 My while loop is called when there is data in the list, with an if statement to determine whether the 
 element exists in the list already. If its true and the number exists, the pointers are changed to move the 
 node with the existing data to the front of the list at head -> next.
 If this is not true and the existing data is not in the list then a new node is created and sent to the back of the
 list again by arranging the pointers. The size is then incremented when the insert function adds a new element.
 */
void list :: insert(int din)
{
	node *p = head -> next;
	node *pp = head;
			
	while (p)
	{
		
		if ( (p -> data) == (din+1))
		{
			pp -> next = p -> next;
			p -> next = head -> next;
			head -> next = p;
			return;
		}
		p = p -> next;
		pp = pp -> next;
	}
			node *new_node_back =  new node();
			new_node_back -> data = din + 1;
			new_node_back -> next = NULL;
			pp -> next = new_node_back;
	N++;
	
}
/*
 Operator overloads the << operator and created a node p in the list and declares it to be head -> next
 After checking to see that p exists, I output the numbers between 2 and 11 with if/else statements to 
 output the instances where the elements match to a name (Ace/King/Queen) and changes the pointer to the next node
 and returns this output
 */

ostream & operator<<(ostream &out, const list &L)
{
	list :: node *p = L.head -> next;

	
		while (p != NULL)
		{
			if ( 11 > ( p -> data) && ( p -> data) != 1)
			{
				out << p -> data <<  " ";
			}

			else 
				if (p -> data == 1)
				{
					out << "Ace ";
				}

			else
				if (p -> data == 11)
				{
					out << "Jack ";
				}

			else
				if (p -> data == 12)
				{
					out << "Queen ";
				}

			else
				if (p -> data == 13)
				{
					out << "King ";
				}

			p = p -> next;
		}
	
	return out;
}
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
	list card_list[4] = {}; // instance of list of arrays initialized to zero
	int deck[4][13]= {0}; // 2D array with 4 rows and 13 columns initialized to zero
	
	bool done = false; //while loop condition: checks to see if terminating condition has been met
	int n = 0; // variable to note what suit program ended

	
	while (!(done)) {
	  string card = random_card(verbose);
	  string garbage= "of";
	  stringstream ss;
	  ss.str(card);

	  string face2, suit2;
	  ss >> face2 >> garbage >>  suit2;
	  
	// done = false;

	// for loop checks face and suit, if matching will add the elements onto the list through the insert function
		  for (int j=0; j< 13; j++)
		  {
			if (face2 == face[j] )
				{
					for (int i = 0; i < 4; i++)
							{
								if ( suit2 == suit[i])
								{
									card_list[i].insert(j);
								}
							}
				}
					
		  }
	//for loop adds to the deck, needed in this program for stopping criteria
		  for (int l = 0; l < 13; l++)
		  {
			  for (int k = 0; k < 4 ; k++)
			  {
					if (( face2 == face[l]) && (suit2 == suit[k]))
					{
						deck[k][l]++;
					}
			  }
		  }

	  
	// string of if statements check stopping criteria and will break if program has at least one of each face card
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
	//suit[i] sets the suit names on the far left, then adds onto the card list
	for (int i=0; i < 4; i++)
	{
		cout << setw(8) << right << suit[i] <<  " : ";
		
		  cout << card_list[i];
	  			
		
		// checks the suit index where the terminating conditions were met and outputs a "**" at the end of the array row (i index)
		if (n == i)
		{
			cout << "**";
		}
		//new line between each row
		cout << endl;
	}	// print formatted table contents to stdout 	
}
