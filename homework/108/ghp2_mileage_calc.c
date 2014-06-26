//	milage HW1 by mat utter
//	Sept 9, 2012
//
//	takes some input does math and spits out a result 
// 
//	Language: C (tcc target)
////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#define reimbursement_rate .55


int main()
{
here:;

double odometer_start, odometer_end, difference, amout_of_reimbursement;

printf("What is the odometer at strip start?   ");
scanf("%lf", &odometer_start);
printf("What is the odometer at strip end?   ");
scanf("%lf", &odometer_end);

difference = odometer_end - odometer_start;
amout_of_reimbursement = difference * reimbursement_rate;

if ( amout_of_reimbursement < 0 ) { printf("\n\n	ERROR: Odometer cannot go backwards!!!\n\n\n"); goto here;}

printf("\n	You will be reimbursed for %4.2lf miles \n	at a rate of $%4.2lf per mile. \n	You will recieve $%4.2lf.\n\n", difference, reimbursement_rate,amout_of_reimbursement);








return 0;

}
