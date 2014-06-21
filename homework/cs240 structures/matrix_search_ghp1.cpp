//GHP1 really simple matrix search
//language: C++ (g++ target 4.6.3)
//written by: Mathew C Utter
//Jan 2010
#include <iostream>
#include <cstdlib>
#define SEED 150 //gives a good variation
#define msize 10 
using namespace std;

bool match(int ary[][msize], int value, int &x_row, int &y_col);
void fill(int ary[][10], int key);
void display(int ary[][msize], int &x_row, int &y_col);

int main(void)
{
int ary[msize][msize],x_col,y_row,key;
cout<<"This program creates a 2D matrix with 100 random integers (0-250), just enter a key number to search for"<<endl;
cout << "Enter a key:";
cin >> key;
cout << endl;

fill(ary,key);
display(ary,x_col,y_row); //using reference to reduce mem aloc
if (match(ary,key,x_col,y_row))
		cout << endl << "Key[" << key << "]@ary[" << ++x_col << "][" << msize-y_row << "]" << endl;
else
	cout << endl << "Key was not generated in matrix." << endl;
return 0;
}

void fill(int ary[][10], int key)
{
//*FILL* 2D matrix with unique integers
//language: C++ (g++ target 4.6.3)
//written by: Mathew C Utter
//Jan 2010
int x_col,y_row, unique, mpt, mpt2;
srand(time(NULL));// getting psuedo random from the *timemicrotonic* if unix
for(y_row=0;y_row<msize;y_row++)
  for(x_col=0;x_col<msize;x_col++)
		{
		unique = (rand()%SEED);//Creates unique numbers only
		if (!match(ary,unique,mpt,mpt2))//when there is no match the unique number is
			ary[x_col][y_row] = unique;//entered into the matrix
		else
			x_col--; // or it takes a step back and tries again
		}
}

void display(int ary[][msize], int &x_row, int &y_col)
{
//*DISPLAY* a 2D matrix w/ X & Y borders
//language: C++ (g++ target 4.6.3)
//written by: Mathew C Utter
//Jan 2010
for(y_col=0;y_col<msize;y_col++)
	{
	cout << "Y" << msize-y_col;
  for(x_row=0;x_row<msize;x_row++)
		cout << "\t" << ary[x_row][y_col]; 
		cout << endl;
	}
for(x_row=0;x_row<msize;x_row++)
	cout << "\t" << "X" << x_row+1;
return;
}

bool match(int ary[][msize], int value, int &x_col, int &y_row)
{
//matrix search and *MATCH* function: searches 2D array for
//a key, returns TRUE if found else FALSE. coordinates are passed by reference
//language: C++ (g++ target 4.6.3)
//written by: Mathew C Utter
//Jan 2010
for(y_row=0;y_row<msize;y_row++)
  for(x_col=0;x_col<msize;x_col++)
    if(value == ary[x_col][y_row])
		return true;
return false;
}
