////////////////////////////////////////////////////////////////
///	GHP 5 Weather stuff v2
///	BY MATHEW UTTER
///	this program takes some input from a number of
///	days and does some stuff with the data
///	such as: catagorize and tally like days based on
///	temp
///
///	compiled with TCC (10/13/2012)
///	compiled with GCC (10/13/2012)
////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hi_temp 85
#define med_temp 60



int main(void)
{

printf("Welcome to mats Weather & Stuff program!!!\n\n");
printf("Low temperatures below 60 degrees, are catagorized as 'LOW'\n");
printf("Pleasent temperatures are between 60 and 85 are 'MED'\n");
printf("Hot temperatures 85 degrees and higher are 'HIGH'\n");
printf("After entering the temperatures type 'done' to end input\n\n");

int hcount=0, mcount=0, lcount=0, i=0, day_count=1, ignore_inp=0;

double av_temp=0, days[2000];
char buffer[256];

printf("When you are finished entering temperature enter 'done'\n");
while(i == 0)
	{

	printf("Enter the temperature for \t day %d: ",day_count);
	gets(buffer);

	if(strcmp(buffer,"done")==0) i = 1;

	days[day_count] = atof(buffer);
	day_count++;
	}

printf("__________________________________\n");

for(i=0;i<day_count;i++)
	{
			if(days[i] >= 85)
			{
			if(i!=0 && days[i]!=0) printf("Day %d  |      %.3lf\t|  HIGH\n", i, days[i]);
			hcount++;
			} else if(days[i] >= 60)
			{
			if(i!=0 && days[i]!=0) printf("Day %d  |      %.3lf\t|  MED \n", i, days[i]);
			mcount++;
			} else
			{
			if(i!=0 && days[i]!=0) printf("Day %d  |      %.3lf\t|  LOW \n", i, days[i]);
			lcount++;
			}


		av_temp = av_temp + days[i];
	}

av_temp = av_temp/(i-2);
lcount = lcount-(2);
//because the atof function i use 'done' and start day_count
//	 at 1, 2 must be subtracted to accurate represent days.

printf("Average temperature: \t%.3lf\n",av_temp);
printf("Low days: %d\tMedium days: %d\tHigh days: %d\n\n",lcount,mcount,hcount);


return 0;
}
