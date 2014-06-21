//GHP2 really simple matrix traversing
//language: C++ (g++ -v 4.7.2)
//written by: Mathew C Utter
//Feb 2013
#include <iostream>
using namespace std;
#include "ghp2.h"

int main(void)
{
int msize;
cout<<endl
		<<"This program queries the user for "
		<<"entries in 2 matrices."
		<<endl
		<<"It will then create a third with sum of the first two "
		<<"and display the results to the screen."
		<<endl;

cout<<"Enter the sqr root of the matrix: ";
cin>>msize;

MAKE_MATRIX matrixA(msize), matrixB(msize), sum(msize);

cout<<endl<<endl<<"Matrix A:"<<endl;
matrixA.make();
cout<<endl<<endl<<"Matrix B:"<<endl;
matrixB.make();

cout<<endl<<endl<<"Matrix A:"<<endl;
matrixA.show();
cout<<endl<<endl<<"Matrix B:"<<endl;
matrixB.show();

cout<<endl<<endl<<"Sum of Matrix A & B:"<<endl;
sum.add(matrixA.ary,matrixB.ary);
sum.show();

delete(matrixA.ary,matrixB.ary,sum.ary);
return 0;
}
