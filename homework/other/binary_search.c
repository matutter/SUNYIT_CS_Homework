////////////////////////////
// BY MAT UTTER
// Compile with GCC 4.7.2
////////////////////////////////////////////////////////
//
// non recursive binary search for 1000 ordered numbers
//
////////////////////////////////////////////////////////



#include <stdio.h>

#define num 1000

int main(void)
{

int array[num];
int high, low, pos, key, i;
for(i=0;i<num;i++) array[i]=i;
for(i=0;i<num;i++) printf("%d ", array[i]);

printf("\nBetween 1 - 1000, what would you like to search for\n");
scanf("%d", &key);

high=num;
low=0;

while( key != pos )
{
	pos = (high + low)/2;
	printf("looking at %d\n", pos);
	if( key > pos ) low = pos;
	if( key < pos ) high = pos;
}
if( key == pos ) printf("\n\nfound it!!!\n\n");

return 0;
}
