//Decimal base converter - enter a decimal number and change the base between 2 and 9
//language: C++ (g++ target 4.6.3)
//written by: Mathew C Utter
//Jan 2010

#include <iostream>

using namespace std; //one scope

int pow(int base, int power);

int main(void)
{
int num, base, power, x, i; // gets sloppy with the leading 0, sorry so i made this i to detect the first pass in the algorithm
while ( base < 2 || base > 10 )
	{
	cout<<endl<<"What base to convert to:\t";
	cin>>base;
	if(base==0) break;
	}

while ( base != 0 || power != 0 )
	{
	cout<<"What # to convert (0 to stop)\t";
	cin>>num;
	if(num==0) break;
	
	for ( power = 0; pow(base,power) < num; power++);
	i=0;

	cout<<endl<<"The result is: ";
	for ( power; power >= 0; power--)
		{
		x=0;

		if ( pow(base,power) <= num )
			{
			while ( num >= pow(base,power) )
				{
				num = num - pow(base,power);
				x++;
				}
			}
		if(i!=0 || x!=0) cout << x;
		i++;
		}
	cout << endl << endl;
	}
return 0;
}

int pow(int base, int power)
{
// POW function, like the thing i could have just use <cmath> for
//language: C++ (g++ target 4.6.3)
//written by: Mathew C Utter
//Jan 2010
int result, i;
result = 1;

for ( i=0; i < power; i++ )
	{
	//cout<<base<<"^"<<i<<" = "<<result<<endl;	
	result *= base;
	}
return result;
}