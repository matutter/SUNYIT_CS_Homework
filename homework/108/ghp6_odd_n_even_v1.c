////////////////////////////////////////////////////////////////////////////////////////
//  By: Mathew C Utter
//  GHP 6 odd n' even v1
//  this program does a numer of things
//  detect multiples: 7, 11, 13
//  detect the sum of digits is even or odd ( 123 = 1 + 2 +3 = 6 = even )
//  detect prime numbers
//  uses some ref params to push data between functions
//  compiled with TCC & GCC(latest as of 10/29)
//  10/23/2012
//////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_data(int data[6][2000], int *count);
void do_math(int data[6][2000], int i, int *prime, int *sum, int *seven, int *eleven, int *thirteen);
//void find_sum(int data[6][2000], int *sum)


int main(void)
{

int count = 0, data[6][2000];


printf("This program does things with integers.\n");
printf("Just type a bunch of integers, separate by new lines, and type 'done'. \n");
printf("We'll let you know information on those numbers.\n");
printf("\nAfter input type 'done'\n");

get_data(data, &count);

int i = 0;
for(i=0;i<count;i++)
	{
	int prime = 0, sum = 0, seven = 0, eleven = 0, thirteen = 0; // so they re initialiaze each loop

	do_math(data, i, &prime, &sum, &seven, &eleven, &thirteen);
	//data[0][i] = input
	data[1][i] = prime;
	data[2][i] = sum;
	data[3][i] = seven;
	data[4][i] = eleven;
	data[5][i] = thirteen; 
	}





//prints out everything
//																							maybe make a second char array so you can make it prettier? 
/////////////////////////////////////////////////////
	int x=0;
	printf("num\tprime\tsum\t7\t11\t13\n");
	for(i=0;i<count;i++)
		{
		for(x=0;x<=5;x++)
			{
			if( data[0][i]%2 == 0 ) //remove these two if statements to open up the results to odds as well
			printf("%d\t",data[x][i]);
			}
		if( data[0][i]%2 == 0 ) //remove these two if statements to open up the results to odds as well
		printf("\n");
		}

return 0;
}

int get_data(int data[6][2000], int *count)
{
//////////////////////////////////////////
// I like this function, I know i didn't
// stick in in main, but there are 3
// ref params used, and this is much
// more tidy
//////////////////////////////////////////

char buffer[256];
int control = 0, i = *count;

while( control == 0 )
	{
	gets(buffer);
	if( strcmp(buffer, "done")==0 ) control = 1;
		else { data[0][i] = atof(buffer);
					i++;
					}
	}
*count = i;

return data[0][2000];
}


void do_math(int data[6][2000], int i, int *prime, int *sum, int *seven, int *eleven, int *thirteen)
{



//the initial values are set in the for loop to make each 
//pass through the array have the same variable values
//to be tested against, of course, not 'i' though.
///////////////////////////////////////////////////////////////// finds prime

	int x = 2, buff = 0, primeb = 0;
	while( primeb != 1 && x < 10)
		{
		buff = data[0][i]%x;
		if(buff == 0 && data[0][i] != x) primeb = 1;
		x++;
		}
	if(primeb == 1) 
		{
		*prime = 0;
		} else *prime = 1;
	if(data[0][i] == 0 || data[0][i] == 1) *prime = 0; 

//The below could also be a recursive function, with pointers
//but this was easier to read
///////////////////////////////////////////////////////////////////////// sum of ints

	int num = 0, part = 0; //*sum = 0;
	num = data[0][i];
	do
		{
		part = num % 10;
		num = num / 10;
		*sum = *sum + part;
		}while(num > 10);
		part = num % 10;
		num = num / 10;
		*sum = *sum + part;


//if statements were the easiest way, too bad these weren't
//7 11 15, something that could be incremented with nested for loops
/////////////////////////////////////////////////////////////////////////// find multiples


	if( data[0][i] % 7 == 0 ) *seven = 1;
		else *seven = 0;
	if( data[0][i] % 11 == 0 ) *eleven = 1;
		else *eleven = 0;
	if( data[0][i] % 13 == 0 ) *thirteen = 1;
		else *thirteen = 0;
	if( data[0][i] == 0 )
		{
		*seven = 0; 
		*eleven = 0; 
		*thirteen = 0; 
		}

	return;
}

