///////////////////////////////////////////////////
//  GHP8 UPC CHECK
//  BY: Mathew Utter
//  11/6/2012
//
//  This program verifies if a UPC is valid
//  or not based on the checksum
//
//  Compiled for GCC 4.2.1 & 4.6.3 & TCC
//
////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#define size 12
#define adjsize 11

void get_input(int container[12]);

int main(void)
{
printf("IN OBJ: main<---\n");
int i=0, buffer=0, pos=0, neg=0, check=0;
int  container[size];
//int sample[12] = {6,8,1,1,3,1,7,0,0,0,8,5};
//char cbuff[12] = {get_input()};
//printf("%s",cbuff);


get_input(container);

for(i=0;i<12;i++)
        printf("%d ",container[i]);
        printf("\n");

for(i=0;i<adjsize;i++)
        if(i%2==0||i==0)
        	neg = neg + container[i];
			else
				pos = pos + container[i];
  

buffer = neg*3;
buffer = buffer + pos;
if(buffer%10==0) check = 0;
        else check = 10 - (buffer%10);
printf("\nChecksum:\t%d\n",check);

if(container[adjsize]==check) printf("\t\tVALID UPC\n");
        else printf("\t\tINVALID UPC\n");



printf("\n");
return 0;
}


void get_input(int container[12])
{
/////////////////////////////////////////////////////////
//  GET_INPUT by Mathew Utter
//  gets a 12 digit UPC input as a char array
//  checks it to make sure only number chars
//  have been entered, and makes them an int.
//  Seems kinda 'hack ish' but standard ASCII
//  has been standard since... even the version
//  of GCC dognet uses, so I'm assuming its
//  a safe case to do this.
//  and arrays are passed by ref. 
printf("IN OBJ: get_input<---\n");
char buffer[size];
int i=0, ctrl=0;

while(ctrl==0)
        {
        printf("Please Enter a UPC code:\t");
        fgets(buffer, 13, stdin);

        for(i=0;i<size;i++)
                if(buffer[i]<48 || buffer[i]>57)
                        {
                        ctrl=0;
                        printf("\nINPUT ERROR<---numbers only.\n\n\n");
                        break;
                        }
                        else ctrl = 1;
        }
        for(i=0;i<size;i++) container[i] = buffer[i]-48;

return;
}