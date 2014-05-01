////////////////////////////
// BY MAT UTTER
// Compile with GCC 4.7.2




#include <stdio.h>



int main(void)      
{

int array[14]={54,47,632,12,14,1,2,3,45,89,6,32,1,4};
int num=14, i, x, buffer;

printf("Before the sort:\n");
for(i=0;i<num;i++) printf("%d,  ",array[i]);

for( i=0; i<num; i++)
	{ 
	for( x=0; x<num-i; x++)
		{
		if( array[x] > array[x+1])
			{
			buffer = array[x];
			array[x] = array[x+1];
			array[x+1] = buffer;
			}            
		}                
	}

printf("\n\nAfter the sort:\n");
for(i=1;i<=num;i++) printf("%d,  ",array[i]);
printf("\n\n");


return 0;
}
