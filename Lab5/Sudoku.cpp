/*
	Author: Sam Steinberg
	Date: October 22nd, 2017
 */
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class sudoku {
	public:
	sudoku();

	void solve();

    void read(const char *);
    void write(const char *);
    void write(const char *, const char *);

  private:
    bool solve(int, int); //recursive solve

    bool error_check_value(int , int, int); //error check for value
    bool uniqueness(int, int); // determines uniqueness to pass to error_check_uniqueness
	bool error_check_uniqueness(); // Determines from uniqueness
	vector<int> valid_values(int, int); //returns a vector of valid values
    void display();

    int game[9][9];
};
/*
	Takes in a coordinate, will activate when the value at the coordinate is zero. Then goes through all the possible numbers (1-9)
	and sets  the game coordinates to k. The uniqueness function is then called to check the coordinate to see if it is unique, and if 
	so is pushed back onto the vector. Then, the game is reset to zero after the valid values have been determined.
 */
vector<int> sudoku::valid_values(int i, int j)
{
	vector<int> valid_values;
	if (game[i][j] == 0)
	{
		for ( int k = 1; k < 10; k++)
		{
			game[i][j] = k;
			if (uniqueness(i , j) == true)
			{
				valid_values.push_back(k);
			}
			game[i][j] = 0;
		}
			
	}
	return valid_values;
}
/*
	bool flag is set to true, uses the uniqueness function to determine is a coordinate is a unique value or not. If not, the flag is 
	set to false denoting an error has been found. If not, the flag stays true.
 */
bool sudoku::error_check_uniqueness()
{
	bool err = true;
	for (int k=0; k < 9; k++)
	{
		for (int l=0; l < 9; l++)
		{
			if (!(uniqueness(k,l)))
			{
					cerr << k  << " " << l << " " << game[k][l] <<  " Illegal non-unique value" << endl;
					err = false; //error found in uniqueness
		}}
	}
	return err; //No error found
}

//False denotes an invalid move, checked in error_check_uniqueness
bool sudoku::uniqueness(int i, int j)
{
	//Activated when the game value is not zero
	if ( game[i][j] != 0)
	{
		//Error checking column through looping through values
	for (int k = 0; k < 9; k++)
	{
		if ( k != j &&  game[i][k] == game[i][j])
		{
			return false;
		}
		
	}
	
	
	
		//Error checking rows through looping, same as column
		for (int a = 0; a < 9; a++)
		{
			if ( a != i && game[a][j] == game[i][j])
			{		
				return false;
			}
			
		}
	
	
	//Validity in box through algorithm checking each value in box and row/column
	for (int s = (i/3)*3; s < (i/3)*3+3; s++)
	{
		for (int t = (j/3)*3; t < (j/3)*3+3; t++)
		{
			if ( s != i && t != j && game[s][t] == game[i][j]){	
					return false;
			}
		}
	}
	}

	return true; // Valid move

	

}
//Passed in a min, max, and v will be the value of the game at the given coordinate
bool sudoku::error_check_value(int min, int max, int v)
{

	if (v < min && v > max)
		return false;

	return true; //true denotes valid value
}

sudoku::sudoku() { 
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++)
      game[i][j] = 0;
  }
}

void sudoku::solve() {
  cout << "SOLVE\n";
  // call recursive computation
  solve(0, 0); //Begins at index (0,0)
  display();

}

void sudoku::read(const char *fname) {
  cout << "READ\n";

  ifstream fin(fname);
    
  int i, j, v;
  int flag = 0; // Flag raised when error
  while (fin >> i >> j >> v) {
    // error check grid indices
	if ( i < 0 || i > 8 || j < 0 || j > 8)
	{
		cerr << i << " " << j << " "  << v <<  " Illegal grid index" << endl;
		flag = 1;
	}
	else{

    game[i][j] = v;
	}
  }

  fin.close();

  // exit if bad grid indices
	if (flag == 1)
	{
		exit(0);
	}
	display();
  // error check data values, manually inserting a min/max value and also the value of the game
	int value_flag = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (error_check_value(1, 9, game[i][j]) == false)
				{	
					value_flag = 1;
				}
	}
	}
  // error check uniqueness
  if(error_check_uniqueness() == false)
  {
		value_flag = 1;
  }
  // exit if errors detected
  if (value_flag == 1)
  {
		exit(0);
  }
}

void sudoku::write(const char *fname) {
  ofstream fout(fname);

  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (0 < game[i][j]) {
        fout << i << " "
			 << j << " "
		     << game[i][j] << "\n";
      }
    }
  }

  fout.close();
}

void sudoku::write(const char *fname, const char *addon) {
  int N1 = strlen(fname);
  int N2 = strlen(addon);

  char *n_fname = new char[N1+N2+2];

  // strip .txt suffix, then concatenate _addon.txt
  strncpy(n_fname, fname, N1-4);
  strcpy(n_fname+N1-4, "_");
  strcpy(n_fname+N1-3, addon);
  strcpy(n_fname+N1-3+N2, ".txt");

  write(n_fname);

  delete [] n_fname;
}

void sudoku::display() {
  cout << "| ----------------------------- |\n";
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
	  if (j%3 == 0) 
	    cout << "|";
      cout << "  " << game[i][j];
	}
    cout << "  |\n";
	if (i%3 == 2)
      cout << "| ----------------------------- |\n";
  }
}

bool sudoku::solve(int i, int j) {
		//If rows hit 9 (out of bounds), reset to 0 to loop around board and increment column
		if ( i == 9 )
		{
			j++;
			i = 0;
		}	
	
	// When column hits 9 the game will be over
	if (j == 9)
	{
			return true;
	}
	
//When the game value at a coordinate isnt zero, increment to the next space and solve
	if ((game[i][j] != 0))
	{
		return solve(i+1, j);
	}

 //Vector to store the valid values at coordinates i and j
  vector<int> values = valid_values(i , j);
//Sets the game value to the valid values at the given point, bad values filtered out in member functions
  for (unsigned int m  = 0; m < values.size(); m++)
  {
	
	  game[i][j] = values[m];
		//Then increments
			if (solve(i+1,j))
				return true;
  }
 

  //Resets game board and returns
  game[i][j] = 0;
	return false;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  if ((argc != 3) ||
      (strcmp(argv[1], "-s") != 0) ||
	  strstr(argv[argc-1], ".txt") == NULL) {
    cerr << "usage: Sudoku -s game.txt\n";
	exit(0);
  }

  sudoku sudoku_game;

  if (strcmp(argv[1], "-s") == 0) {
    sudoku_game.read(argv[2]);
    sudoku_game.solve();
    sudoku_game.write(argv[2], "solved");
  }
}
