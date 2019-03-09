/*
	Author: Sam Steinberg
	Date: November 9th, 2017

*/
#ifndef BST_H
#define BST_H

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class TKey>
class bst {
  struct node {
    node(int id=0) { ID=id; parent = NULL;} //Constructor takes an integer which serves as the ID, parent set initially to null for root

	void print();

    TKey key;
//	ID parameter
	int ID;
//	parent info
    node *link[2];
	node *parent;
  };
  //iterator class operator function definitions
  public:
	class iterator {
	  public:
		iterator() {p=NULL;}
		iterator operator++();
		bool operator==(const iterator &) const;
		bool operator!=(const iterator &) const;
     	TKey & operator*();

	  private:
	    friend class bst<TKey>;
		iterator(node *P) { p=P;}

	    node *p;
	};

  public:
    bst() { Troot=NULL; ID = 0;}
	~bst() { clear(Troot); }

	bool empty() { return Troot==NULL; }

	void insert(TKey &);

	iterator lower_bound(const TKey &);
	iterator upper_bound(const TKey &);
	iterator begin();
	iterator end();
	void print_bylevel();

  private:
	void clear(node *);
	node *insert(node *, TKey &);

//	ID parameter
	int ID;
    node *Troot;
};
template <class TKey>
typename bst<TKey>::iterator bst<TKey>::lower_bound(const TKey &T1)
{
	
	node *q = Troot;
	node* t = NULL;

	while(q) //While there are values in the tree
		{
			if (T1 <= q->key) //Value less than or equal the root value
			{
				t = q; // node t holds the place where q was
				q = q->link[0]; // q incremented to its left link
			}
			else
				q = q->link[1]; // q will then go to the right
		}
				return iterator(t); //saved root node if nothing is greater in left side of tree
		
}

template <class TKey>
typename bst<TKey>::iterator bst<TKey>::upper_bound(const TKey &T2)
{
	node *q = Troot;
	node* t = NULL;

	while(q) //While there are values in the tree
		{
			if (T2 >= q->key) //Value greater than or equal the root value
			{
				q = q->link[1]; //q now points to its right node, which is greater
			}
			else{
				t=q; //Place holder
				q = q->link[0]; // If q isnt greater than or equal to, set q to its left link
		}}
				return iterator(t); //saved root node if nothing is greater in left side of tree
}
//begin iterator
template <class TKey>
typename  bst<TKey>::iterator bst<TKey>::begin()
{
	node *p = Troot; //set node to root
	if (!p)
	{
		return iterator(p); //null
	}
	while (p->link[0])
	{
		p = p->link[0]; //traverses tree to left most node and updates p along the way
	}

	return iterator(p); // returns left most after traversals
}
//end iterator
template <class TKey>
typename bst<TKey>::iterator bst<TKey>::end()
{
	return iterator(NULL); // next iterator null
}

template <class TKey>
void bst<TKey>::node::print()
{
  cout << setw(3) << key << "   ";

  //output node and parent ID information
  //change below to output subtree ID information
//print out ID's instead of keys, if parent==NULL, it is the root
  if (parent == NULL){
	  cout << ID << " :ROOT  ";
	  if (link[0]) cout << "L=" << setw(3) << link[0]->ID;
	  else cout << "       ";
	  if (link[1]) cout << " R=" << setw(3) << link[1]->ID;
	  else cout << "       ";

	  cout << endl;
  }
  //If it has a parent, which means if it is not the root
  if (parent != NULL)
	{
		cout << ID << " :P=" << setw(3) << parent->ID;  

		if (link[0]) cout << " L=" << setw(3) << link[0]->ID;
		 else         cout << "      ";
		if (link[1]) cout << " R=" << setw(3) << link[1]->ID;
		 else         cout << "      ";

  cout << "\n";
	}
}

//bst<TKey>::iterator functions not defined above go here
template <class TKey>
typename bst<TKey>::iterator bst<TKey>::iterator::operator++()
{
	//Checks to see if p is the only node
	if (!p)
	{
		return *this;
	}
	//Checks to see if node has a right child----returns if no left child, but iterates left at right child so next largest is found
	else
	if (p->link[1]) // When node has a right child...
	{
		p= p->link[1]; // update p to its right child
		while (p->link[0]) // When the parent has a left subtree...
		{
			p = p->link[0]; // p will update to left most in sub tree
		}
		return *this; //pointer to p
	}	
		//if p is a right node of its parent, set p to parent and see if the parent is a left node, and return grandparent
		while (p->parent) //With p's parent
		{
			node *q = p; //set p to be q
			p = p->parent; //set p to be parent
			if (p->link[0] == q) // when p's left node is q...
			{
				return *this; //return p, as it is the parent of q
			}
		}
		p = NULL; //These two lines trigger when p is the right most node
	return *this;
}
template <class TKey>
bool bst<TKey>::iterator::operator==(const iterator &rhs)const
{
	return p == rhs.p;
}
template <class TKey>
bool bst<TKey>::iterator::operator!=(const iterator &rhs)const
{
	return p != rhs.p;
}
template <class TKey>
TKey& bst<TKey>::iterator::operator*()
{
	return p->key;
}

template <class TKey>
void bst<TKey>::clear(node *T)
{
  if (T) {
    clear(T->link[0]);
    clear(T->link[1]);
    delete T;
    T = NULL;
  }
}

template <class TKey>
void bst<TKey>::insert(TKey &key)
{ 
  Troot = insert(Troot, key);
}

template <class TKey>
class bst<TKey>::node *bst<TKey>::insert(node *T, TKey &key)
{
  if (T == NULL) {
  //  update and set node ID
	ID++; //updated before node creation because i set the ID to 0 initially
    T = new node(ID);
    T->key = key;
  } else if (T->key == key) {
    ;
  } else {
   // set parent link
    int dir = T->key < key;
    T->link[dir] = insert(T->link[dir], key);
	T-> link[dir]-> parent = T;
  }

  return T;
}

//bst<TKey>::lower_bound function goes here

//bst<TKey>::upper_bound function goes here

template <class TKey>
void bst<TKey>::print_bylevel()
{
  if (Troot == NULL)
    return;

  queue<node *> Q;
  node *T;

  Q.push(Troot);
  while (!Q.empty()) {
    T = Q.front();
    Q.pop();

    T->print();
    if (T->link[0]) Q.push(T->link[0]);
    if (T->link[1]) Q.push(T->link[1]);
  }
}
#endif
