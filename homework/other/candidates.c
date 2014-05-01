#include <stdio.h>// allows use of printf and scanf

int main (void) //starts he main function
{
 //beginning of main function

//Declaration of my variables, Algothim steps (1-6)
int votes[5][4] = {192, 48, 206, 37, 147, 90, 312, 21, 186, 12,
121, 38, 114, 21, 408, 39, 267, 13, 382, 29};

int row = 0, column = 0, i = 0, c = 0, x= 0;
int total_votes = 0, highest_can = 0, highest_pre =0;
int precinct_votes [5]= {0,0,0,0,0};
int can_votes [4]={0,0,0,0};
int highest_temp =0 ;
int can = 0, pre=0;


for(i=0;i<4;i++) 		printf("\t%c",i+65);
printf("\n");
for(i=0;i<5;i++)
	{
	printf("%d",i+1);
	for(x=0;x<4;x++)
		{
		printf("\t%d",votes[i][x]);
		}
	printf("\n");
	}

//findes totals for candidates
for( i=0; i<4; i++)
	{
	for( x=0; x<5; x++)
		{
		if(i==0) { can_votes[0] = can_votes[0] + votes[x][i]; }//printf("%d ",votes[x][i]); }
		if(i==1) can_votes[1] = can_votes[1] + votes[x][i];
		if(i==2) can_votes[2] = can_votes[2] + votes[x][i];
		if(i==3) can_votes[3] = can_votes[3] + votes[x][i];
		}
	}
//finds totals for precincts
for( i=0; i<5; i++)
	{
	for( x=0; x<4; x++)
		{
		if(i==0) precinct_votes[0] = precinct_votes[0] + votes[i][x]; 
		if(i==1) precinct_votes[1] = precinct_votes[1] + votes[i][x];
		if(i==2) precinct_votes[2] = precinct_votes[2] + votes[i][x];
		if(i==3) precinct_votes[3] = precinct_votes[3] + votes[i][x];
		if(i==4) precinct_votes[4] = precinct_votes[4] + votes[i][x];
		}
	}
//finds highest precinct
for(i=0;i<5;i++)
		if(precinct_votes[i] > precinct_votes[i-1]) 
			{
			highest_pre = precinct_votes[i];
			pre = i;
			}
printf("\n\nThe highest Precinct was %d with %d votes\n\n",
(pre+1), highest_pre);


//finds highest candidate
for(i=0;i<4;i++)
		if(can_votes[i] > can_votes[i-1]) 
			{
			highest_temp = can_votes[i];
			can = i;
			}

for(i=0;i<4;i++) printf(" candidate %c has %d votes\n", i+65, can_votes[i]);

printf("\n\nThe highest Candidate was %c with %d votes\n\n",
(can + 65), highest_temp);


return (0);
}