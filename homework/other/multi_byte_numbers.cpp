//HW2 for CS220 
//language: C++ (g++ -v 4.7.2)
//written by: Mathew C Utter
//March 2013

#include <iostream>
#include <iomanip>
using namespace std;

#define mydata unsigned short

int pow(int base, int power);
mydata get_good_integer(void);

int main(void)
{
mydata maxnum = 0xFFFF, minnum = 0x0, i, mynum;
mydata mask = 1U << (sizeof(mydata) * 8U - 1U), num_bytes = sizeof(int)/sizeof(mydata); //num_bytes was going to be what i'd use to dynamically call a number of the byte chunks, but i ran out of time
mydata hold=0U, hold2=0U;

cout << "Min/Max :: " << minnum << "/" << maxnum << endl;
mynum = get_good_integer();
cout << "This fits in " << num_bytes << " octets " << endl << endl
     //<< "" << endl
		 << "Number binary : ";

for(i = (sizeof(mydata) * 8U )/ num_bytes; i!=0; i--)
{
    if( !(mynum & mask) )
        cout << "0";
    else
    {
    	cout << "1"; hold = hold + pow(2U,i);}
        mask  >>= 1;
    }

//cout << "_";

	for(i = (sizeof(mydata) * 8U )/ num_bytes; i != 0; i--)
   {
      if( (mynum & mask) == 0 )
				{cout << "0";}
      		else
         		{cout << "1"; hold2 = hold2 + pow(2U,i);}
      mask  >>= 1;
   }

hold >>= 0x1;
hold2 >>= 0x1;

cout << endl << "First integer : " << setfill('0') << setw(8) << hold << endl
		 << "Second integer: \t" << setfill('0') << setw(8) << hold2 << endl;


cout << endl << endl << "*** The leading zeros are just formatting" << endl;
return 0;
}

mydata get_good_integer(void)
{
// Get a Good Integer within a range 
//language: C++ (g++ target 4.6.3)
//written by: Mathew C Utter
//March 2010
int mynum;
cout << "Enter a number from min to max:";
cin >> mynum; 
if ( mynum <= 0xFFFF && 0x0 <= mynum ) return mynum;
	else mynum = get_good_integer();
}

int pow(int base, int power)
{
// POW function, like the thing i could have just use <cmath> for
//language: C++ (g++ target 4.6.3)
//written by: Mathew C Utter
//Jan 2010
int result, i;
result = 0x1;

for ( i=0x0; i < power; i++ )
	result *= base;
	
return result;
}
