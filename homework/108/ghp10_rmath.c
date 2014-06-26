//////////////////////////////////////////////////////////////////////
//  BY Mat Utter
//  does some math visa ve a recursive function
//  COMPILED FOR GCC 3.6.2
//  f(x) =0	 if x <=0
//  f(x)=f(x-1)+(x-3)	otherwise 
//  To test your program compute f(2) - the answer should 
//  be -3....if it is not your program is incorrect.
//  
///////////////////////////////////////////////////////////////////////
#include <stdio.h>

int f(int x);

int main(void)
{
// unecessary since x will be written do from stdin before math
int x=0;

printf("\nEnter a value for X:\t");
scanf("%d",&x);

printf("\n\nBefore the math you entered %d, ",x);
x=f(x);

printf("and the result is %d.\n\n", x);

return 0;
}


int f(int x)
{
//////////////////////////////////////////
//  BY MAT UTTER
//  A simple recursive function for
//  doing some arithmatic.

//  same thing but a character less 
if(x>0) x=f(x-1)+(x-3);
	else
		x=0;

//printf("Value for X = %d\n\n", x);
return x;
}
