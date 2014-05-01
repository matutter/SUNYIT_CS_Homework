////////////////////////////
// BY MAT UTTER
// Compile with GCC 4.7.2
//
// detects or makes a palendrome
/////////////////////////////


#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(void)
{
char forward[20], backward[20];
int i, c, x;



printf("type a word to test for palindrome\n\n");

gets(forward);
strcpy(backward, forward);

for (i = 0, x = strlen(backward)-1; i < x; i++, x--) 
{
c = backward[i];
backward[i] = backward[x];
backward[x] = c;
}

if( strcmp(forward, backward)==0 ) 
printf("yep... thats a palindrome.\n");
else
printf("nope... thats not a palindrome.\n");
strcat(forward, backward);
printf("but now it is! %s\n\n", forward);



return 0;
}
