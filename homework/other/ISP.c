////////////////////////////
// BY MAT UTTER
// Compile with GCC 4.7.2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


void do_charges(int i, double data[10], double *cph, double *ave_cost);
double round_money(double money);

int main(void)
{

int i=0, n=0;
double id_buffer=0.0, val_buffer=0.0, data[10], cph = 0.0, ave_cost = 0.0;
char c;

FILE *fp = fopen("usage.txt", "r");
if(fp == NULL ) printf("error\n");

	while ( c != EOF )
	{
//do {
	//for(i=0;i<4;i++)
	//	{
		fscanf(fp,"%lf %lf", &id_buffer, &val_buffer);
		data[i] = id_buffer;
		data[i+4] = val_buffer;
	//	}
	c = getc(fp);
	i++;
	}
//	}while ( c != EOF );
fclose(fp);

fp = fopen("charges.txt", "w");
if(fp == NULL ) printf("error\n");

fprintf(fp,"Charges for %0.0lf/%0.0lf\n\n\n", data[0], data[4]);
fprintf(fp,"Customer\t Hours used\t C.P.H.\t\t Ave. Cost\n\n");


printf("Charges for %0.0lf/%0.0lf\n\n\n", data[0], data[4]);
printf("Customer\t Hours used\t C.P.H.\t\t Ave. Cost\n\n");
for(i=1;i<4;i++)
	{
	cph = 0;
	do_charges(i, data, &cph, &ave_cost);
	fprintf(fp,"%1.0lf\t\t %0.2lf\t\t %0.2lf\t\t %0.2lf\n\n",data[i], data[i+4], cph, ave_cost);
	printf("%1.0lf\t\t %0.2lf\t\t %0.2lf\t\t %0.2lf\n\n",data[i], data[i+4], cph, ave_cost);

	}
fclose(fp);
return 0;
}

void do_charges(int i, double data[10], double *cph, double *ave_cost)
{
int base_rate = 7.99, partial_rate = 1.99;
double remain=0.0, total_hours=0.0, money=0.0;

/*
printf("%6.0lf %6.0lf\n", data[0], data[4]);
for(i=1;i<4;i++)
	{
	printf("%6.0lf %6.2lf\n", data[i], data[i+4]);
	}
*/

	if(data[i+4] > 10) 
		{
		remain = data[i+4] - 10;
		while(remain > 0)
		{
		*cph = *cph + 1.99;
		if(remain/10>0) remain--;
		}
		*cph = *cph + 7.99;
		money = *cph;
		*cph = round_money(money);
		total_hours = (remain * *cph);
		//printf("Customer %6.0lf, uses %6.2lf hours, is charged %6.2lf\n", data[i], data[i+4], total_hours);
		
		} else {

		*cph = 7.99;
		money = *cph;
		*cph = round_money(money);
		total_hours = data[i+4] * 7.99;
		//printf("Customer %6.0lf, uses %6.2lf hours, is charged %6.2lf\n", data[i], data[i+4], total_hours);
		}
	
		*ave_cost = *cph / data[i+4];
		money = *ave_cost;
		*ave_cost = round_money(money);
		
		//printf("%6.2lf\n", ave_cost);
}

double round_money(double money)
{

money = money * 100;
money = round(money);
money = money / 100;

return money;
}
