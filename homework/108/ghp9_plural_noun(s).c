//////////////////////////////////////////////////////////////
//		GHP9_plural_nouns.v BY Mathew C Utter
//		11/14/2012
//		COMPILED WITH GCC4.6.2
//
//  Write a program that queries a user for a singular
//  noun and forms its plural according to the following rules:
//
//  1.  If the noun ends in 'y', remove the 'y' and substitute "ies".
//  2.  If the noun ends in 's', "ch", or "sh", add "es".
//  3.  In all other cases add 's'.
//////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

#define SIZE 20
#define RECORD 50

typedef struct 
{
//////////////////////////////////////////////////////
//  WORD BANK ARRAY STRUCT BY MAT C U
//  setting up a simple word bank array struct
//////////////////////////////////////////////////////
char word[21];
char plural[23];
int id;
}word_bank;

int get_input(int i, word_bank record[RECORD]);

int main(void)
{
word_bank record[RECORD];
int i=0, num=0, pos=0;
char buffer[SIZE], *tok;

printf("*maximum word size is 20 characters.\nEnter a string('done' when complete)\n\n");
num = get_input(i, record);


printf("\nThere are %d word(s) in the word bank.\n\n",num-1);

for( i=1; i<num; i++ )
	{
	strcpy(buffer,record[i].word);
	pos = (strlen(buffer)-1);

	if( buffer[pos] == 'y' ) // The concatenation for y to a plural(ies)
		{
		tok = strtok( buffer, "y" );
		while (tok != NULL)
			tok = strtok (NULL, "y");
		strcat(buffer,"ies\n");

		} else
		if(buffer[pos] == 's' || buffer[pos] == 'h' && (buffer[pos-1] == 'c' || buffer[pos-1] == 's') )
			{
			strcat(buffer,"es\n");
			} else
				strcat(buffer,"s\n");

		strcpy(record[i].plural,buffer);
	}
												// when the below prints out see there are two new lines, one from the word
for( i=1; i<num; i++ )
	printf("\t#%d  |  %s\t|  %s\n",record[i].id, record[i].word, record[i].plural);

return 0;
}

int get_input(int i, word_bank record[RECORD])
{
/////////////////////////////////////////////////////////
//  BY MATHEW UTTER
//  this function gets input and stick it in the 
//  struct after removing the new line char
/////////////////////////////////////////////////////////
char buffer[SIZE];

while ( strcmp(buffer,"done\n") != 0 )
	{
	i++; // incrementing I here so word 1 has the id of 1, makes record[0] garbage though
	printf("Word#%d:\t",i);
	fgets(buffer,SIZE,stdin);
	if( strcmp(buffer,"done\n") != 0 )
		{
		buffer[strlen(buffer)-1] = 0;
		strcpy(record[i].word,buffer);
		record[i].id=i;
		}
	}
return i;
}
