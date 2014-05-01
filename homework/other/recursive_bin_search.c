////////////////////////////
// BY MAT UTTER
// Compile with GCC 4.7.2
////////////////////////////////////////////////////////
//
// recursive binary search for 1000 ordered numbers
//
////////////////////////////////////////////////////////


#include <stdio.h>

#define num 1000

void rbins(int array[num], int key, int high, int low);

int main(void)
{

int array[num];
int high=num, low=0, key, i=0;
//for(i=0;i<num;i++) printf("%d ", array[i]+1); <--- not necessary

while(i==0)
	{
	printf("\nBetween 0 - 1000, what would you like to search for\n");
	scanf("%d", &key);
	if(key<=0||key>=num)
			printf("\tINPUT ERROR, values between 1 - 1000 only"); 
				else i = 1;
	}

for(i=0;i<num;i++) array[i]=i; // moved this after input so i can use fewer vaiables and save a line of re-assignment

rbins(array,key,high,low);

return 0;
}

void rbins(int array[num], int key, int high, int low)
{

int pos = pos;
pos = (high + low)/2;
printf("looking at %d\n", pos);
if( key > pos ) low = pos;
if( key < pos ) high = pos;

if( key != pos ) rbins(array,key,high,low);
	else
		printf("\n\nfound it!!!\n\n");

return;
}
