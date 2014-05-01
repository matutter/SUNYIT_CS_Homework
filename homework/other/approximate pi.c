////////////////////////////
// BY MAT UTTER
// Compile with GCC 4.7.2
//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  - Do problem #15 page 310 "Approximate PI" and #17 page 311 "Trapazoid" Hanly 7th Edition 
//  
//  
//  
//  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>


int main(void)
{
double pi=0.0, add_buff=0.0, sub_buff=0.0, buffer=0.0;
int i=0, odds=1.0, blink=1;
int pos=0, neg=0;
for(i=0;i<99;i)
	{
	if(i%2!=0)
		{
		sub_buff = 1.0 / odds;
				buffer = buffer - sub_buff;
	///////////////////////////////////
	i++;
	neg++;
	///////////////////////////////////
		}else{
		add_buff = 1.0 / odds;
				buffer = buffer + add_buff;
	///////////////////////////////////
		i=i+3;
	pos++;
	///////////////////////////////////			
		}

	odds=odds+2.0;

	}
	pi = 4 * ( buffer );

//printf("%d\tevens%d\todds%d\n", odds, pos, neg);
printf("\nthe value for pie is \t%.10lf", pi);
printf("\nshould be \t\t3.1415926535\nthis is because we're doing arithmatic with reals\n");

return 0;
}

