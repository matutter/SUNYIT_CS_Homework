////////////////////////////////////////////////////////////////////////
//  BMI calculate GHP4 
//  10 / 2 / 2012
//  This program prompts the user for height(inches) and weight (lbs)
//  and calculates the british mass index of that data
//  BY: Mathew C Utter
//  COMPILED FOR: GCC & TCC(win) 
////////////////////////////////////////////////////////////////////////

#include <stdio.h>



int main(void)
{
	double wt, ht, BMI;

	printf("Enter your weight(lbs):\t\t");
	scanf("%lf",&wt);

	printf("Enter your height(inches):\t");
	scanf("%lf",&ht);
	// I didn't want to use math.h and pow until I had a response
	// from the last email, since libm.a doesnt include itself 
	// without the -lm argument to the compile command 
	
	BMI=(703*wt)/(ht*ht);

	printf("\nYour BMI is... \t\t\t%2.1lf\n", BMI);
	
	printf("BMI Status...\t\t\t");
	
	if( BMI < 18.5 )
	{
		printf("[ UNDERWEIGHT ]\n");

	} else if ( BMI > 18.5 && BMI < 24.9 )
	{
		printf("[ NORMAL ]\n");

	} else if ( BMI > 24.9 && BMI < 29.9 )
	{
		printf("[ OVERWEIGHT ]\n");

	} else if ( BMI >= 30 )
	{
		printf("[ OBESE ]\n");
	}

printf("\n");

	return 0;
}

/*
BMI	 Status
<18.5	 Underweight
18.5-24.9	 Normal
25.0-29.9	 Overweight
>=30.0	 Obese
 
The formula for BMI is:
 
BMI=(703*wt)/(ht^2)
*/
