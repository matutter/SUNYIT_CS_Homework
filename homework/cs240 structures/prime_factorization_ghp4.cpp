//GHP4 Prime facorization, remember 1 isnt prime or composit!
//language: C++ (g++ -v 4.2.1)
//written by: Mathew C Utter
//March 2013
//using The Stack this finds *prime* *factors* a number
#include <iostream>
#include <stack>
using namespace std;

#define mydata unsigned short

bool isprime(mydata my_num)
{
//determines if an integer is prime by datatype conversion
//language: C++ (g++ -v 4.2.1)
//written by: Mathew C Utter
//Feb 2013
mydata whole;
long double num, di; // just encase
if ( my_num == 2 || my_num==1 ) return true;
for( di=2.0; di!=my_num; di++ ) {
num=(my_num/di);  whole=num;  num=num-whole;
if ( num == 0 ) return false; }
return true;
}

bool isfactor(mydata my_num, mydata test)
{
//determines if a number is a factor of another number
//language: C++ (g++ -v 4.7.2)
//written by: Mathew C Utter
//Feb 2013
if ( my_num % test == 0 )
  return true;
return false;
}

int main(void)
{
mydata my_num, i;
stack<mydata> pfactors;
cout<<endl
		<<"This program finds prime factorization of composit numbers."<<endl 
    <<"Scope of composite numbers found between 0 and 65536."<<endl
		<<"Enter a number:";
cin >> my_num;

if ( my_num <= 0x1) {
  cout << my_num << " is not prime, composit, or in scope." << endl;
  return 0; }

for ( i=0x2; i!=my_num; i++ )
  if(isprime(i) && isfactor(my_num,i))
    pfactors.push(i);
if (pfactors.empty()) {
  cout << my_num << " is prime!" << endl;
  return 0; }
i = my_num;
while (!pfactors.empty()) 
  {
    if (isfactor(i,pfactors.top()))
      {
      i /= pfactors.top();
      cout << pfactors.top();
      if( i != 0x1 ) cout << " * ";
      }
    else
      pfactors.pop();
  }
cout << " = " << my_num << endl;
return 0;
}
