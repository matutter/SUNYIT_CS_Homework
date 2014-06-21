//	Header file for matrix_maker functions
//  makes a matrix from user input
//  displays, and adds two matrixes in the add function
//	adapted super loosely from Ron Saners example.h from cs240
//  Adapted February 2012
//	language: C++ (g++ -v 4.7.2)
//	written by: Mathew C Utter
//	Feb 2013

#include <iostream>
using namespace std;
//#define msize 3

class MAKE_MATRIX
{
  public:
// I'm just leaving all the comments here like a template
// for future assignments... 
/*=======================================================*/
/*function members - prototypes for outlined members*/
/*runs when called*/

	MAKE_MATRIX(int args)
	{
	//allocate space on the heap msize^2 ints
	//language: C++ (g++ -v 4.7.2)
	//written by: Mathew C Utter
	//Feb 2013
		msize = args;

		ary = new int*[msize];	

		for ( x_col=0; x_col<msize; x_col++ )
			ary[x_col] = new int[msize];
		
	//cout<<"*** Matrix created:: @( "<<ary<<" )"<<endl;
	}
/*=======================================================*/
/*Inline function members*/
/*runs everytime class is called*/
/*Constructor Function - would be here*/
/*=========================================================*/
	void make(void)
	{
	//Make a 2D matrix via user input
	//language: C++ (g++ -v 4.7.2)
	//written by: Mathew C Utter
	//Feb 2013
	//cout<<"*** Matrix:: @( "<<ary<<" )"<<endl;

		cout<<"Fill in the matrix with "
				<<msize*msize
				<<" numbers"
				<<endl;

		for(y_row=0;y_row<msize;y_row++)
			for(x_col=0;x_col<msize;x_col++)
			{
			cout<<"Enter for ("<<x_col<<","<<y_row<<"):\t";
			cin>>ary[x_col][y_row];
			}
	}  

	void show(void)
  {
	//show a 2D matrix
	//language: C++ (g++ -v 4.7.2)
	//written by: Mathew C Utter
	//Jan 2010
	//cout<<"*** Matrix:: @( "<<ary<<" )"<<endl;

		for(y_row=0;y_row<msize;y_row++)
			{
			cout<<endl;
			for(x_col=0;x_col<msize;x_col++)
				cout<<ary[x_col][y_row]<<" ";
				}
	cout<<endl;
  }
	
	void add(int **a, int **b)
  {
	//add two matricies and fill a third with the sum
	//language: C++ (g++ -v 4.7.2)
	//written by: Mathew C Utter
	//Feb 2013
	//cout<<"*** Matrix:: @( "<<ary<<" )"<<endl;
	//cout<<"*** Matrix:: @( "<<a<<" )"<<endl;
	//cout<<"*** Matrix:: @( "<<b<<" )"<<endl;

	

		for(y_row=0;y_row<msize;y_row++)
			for(x_col=0;x_col<msize;x_col++)
				ary[x_col][y_row] = a[x_col][y_row] + b[x_col][y_row];
	}

/*=========================================================*/
/*data members of PUBLIC SECTION */
	int **ary, x_col, y_row;

/*END OF PUBLIC SECTION*/
/*=========================================================*/
/*data members of PRIVATE section*/
private:
	int msize;
/*=========================================================*/
}; // END CLASS
