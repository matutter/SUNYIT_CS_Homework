///////////////////////////////////////////////////////////////////////////////////////////
//GHP7 nesty loops by mathew utter																					//
//10/30/2012																																	//
// compiled for TCC & GCC																										//
//																																							//
//Use nested loops - an outer loop that counts from 2 to 30 and						//
//an inner loop that	adds up 1/2 + 1/2 on the first iteration,								//
//1/3+1/3+1/3 on the second iteration,																			//
//1/4+1/4+1/4+1/4 on the third iteration, and so on.  											//
//Note: You must use nested loops; simply multiplying the fraction 				//
//by the appropriate multiplier will not achieve the result that is sought!		//
///////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int main(void)
{
int x=0, y=0;
double sum = 0, frac = 0;

printf("This program shows the issue when doing arithmetic with real numbers.\n");
printf("though things like 14 * (1/14) = 1 should be true, because floating point numbers are\n");
printf("estimated to some degree, errors do occur.\n\n");

for(x=2;x<=30;x++) // outer loop
	{
	sum = 0.0; //some compilers need double to be seeded with atleast one number with a decimal
	frac = 1.0/x;
	for(y=0;y<x;y++) // nested loop
		{
		sum = frac + sum + 0.0; 
		} // end nested
	if(sum==1)
			printf("Adding %d 1/%d's is equal to 1\n", x, y);
	else if (sum < 1)
			printf("Adding %d 1/%d's is less than 1\n", x, y);
	else 
			printf("Adding %d 1/%d's is greater than 1\n", x, y);
	} // end outer
return 0;
}
