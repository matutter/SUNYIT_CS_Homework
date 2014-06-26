////////////////////////////////////////////////////////////////////////////////////////////////////////
//  BY MATHEW C UTTER
//  GHP 12 linked lists
//  12/02/2012
//		
//  GHP #12 (due 12/11) Write a program that utilizes a structure and linked list to
//  store employee information taken from the keyboard (first name, last name, three
//  digit employee id number). The program should traverse the linked list and display
//  the information for the employee with the highest id number.
//
//  Compiled for GCC 4.7.2 & 4.2.1
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noder
{
	int id;
	char fname[20], lname[20];
	struct noder *next;

}NODES;

void get(char buffer[]);
NODES *create(NODES *head, char buffer[]);
NODES *read(NODES *head, char buffer[]);
NODES *find(NODES *point, int idhi, NODES **high);

int main(void)
{
NODES  *head=NULL, *point, **high;
char buffer[20];

printf("Enter data as prompt to create and fill list with employee information.\n");
printf("Please use unique 3 digit employee IDs only.\n");
printf("Type 'done', at any time to end input and show entire list.\n");

head=create(head, buffer); //doing this once before the loop to save the location of the first struct in the list
point=head; //saves the original mem location of the head but passes it for the loop

while( strcmp(buffer,"done") != 0 ) //typing done terminates input
	point=create(point, buffer); //pass the stack pointer and return the new pointer

point->next=NULL; //puts a null at the end of the list
point=head; //make point be the head of the list
printf("\n\n");

while( point->next != NULL ) // will print entire list
	point=read(point, buffer); //passing stackpointer and returning next in list


int idhi; // the below finds and shows the highest ID after list prints
idhi = head->id; // I wanted to put this in a seperate function but 
high = &head; // I couldn't make a pointer to a pointer of a memory location work right
point = head; // like if i said NODES **node = node_with_highest_id_at_the_time 

while( point != NULL )	
	point = find(point, idhi, &(*high));

point = *high; 	//oh well good enough
	
printf("____________________\nHighest employee ID:\n");
printf("Name:\t%s %s\nID:\t%d\n\n", point->fname, point->lname, point->id); // print highest

return 0;
}

NODES *find(NODES *point, int idhi, NODES **high)
{
	if(point->id == idhi) printf("None unique id's used. Not my fault!\n");
	if(point->id > idhi) { idhi = point->id; *high = point; }
	point=point->next;

return(point);
}


NODES *read(NODES *node, char buffer[])
{
/////////////////////////////////////////////////////
//  show all nodes function by Mathew utter
//  Compiled for GCC 4.7.2 & 4.2.1
//
NODES *prev=node;

printf("Name:\t%s %s\nID:\t%d\n", node->fname, node->lname,  node->id); // print all
node = node->next; //storing the new mem loc in node 

return(node); // returning new mem loc
}

NODES *create(NODES *node, char buffer[])
{
/////////////////////////////////////////////////
// create node function by Mathew utter
//  Compiled for GCC 4.7.2 & 4.2.1
//
printf("\n");

char BIGBUFFER[3][20]; // BIGBUFFER is letting me transport the buffer payload from before to
NODES *point=node, *prev=node, *new; // after creation of a new node, so nothing is makde if done is entered.

printf("First name:\t"); //this is all done here to make sure a node isnt created and not filled
get(buffer);
if(strcmp(buffer,"done") != 0 )
	{ 
	strcpy(BIGBUFFER[0],buffer);
	printf("Last name:\t");
	get(buffer);
	if(strcmp(buffer,"done") != 0 )
		{ 
		strcpy(BIGBUFFER[1],buffer);
		do
			{
			printf("ID:\t\t");
			get(buffer);
			if(strlen(buffer)!=3) printf("Employee ID must be 3 characters...\n");
			if(strcmp(buffer,"done") != 0 )
				{ 
				strcpy(BIGBUFFER[2],buffer);
				}
			}while(strlen(buffer)!=3);
		}
	}

if(!(new=(NODES*) malloc(sizeof(NODES)))) printf("bad node...\n"); //new = new memory address OR ELSE!! 

strcpy(new->fname,BIGBUFFER[0]); //put stuff in node(s)
strcpy(new->lname,BIGBUFFER[1]);
new->id=atoi(BIGBUFFER[2]);

new->next=new; //store new's location at the stack pointer in the new node
if(prev != NULL)  //just helps create that first node 
	prev->next=new; //puts the new nodes memloc inside the old node

return(new);
}

void get(char buffer[])
{
///////////////////////////////////////////////
// get input function by Mathew utter
//  Compiled for GCC 4.7.2 & 4.2.1
//
//printf("Input:\t");
fgets(buffer,20,stdin);
buffer[strlen(buffer)-1] = 0;
//printf("\n");
return;
}
