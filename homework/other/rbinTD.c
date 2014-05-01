#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noder
{
	char key[20];
	struct noder *left, *right;

}NODES;

void get(char buffer[]);
NODES *create(NODES *head, char buffer[]);
void read(NODES *head);
NODES *delete(NODES *node, char buffer[]);

int main(void)
{
NODES  *head=NULL, *point;
char buffer[20];

printf("Enter as many keys as you want.\nType 'done' to end input.\nType 'delete' and enter to key you wish to delete.");

head=create(head, buffer); //doing this once before the loop to save the location of the first struct in the list
head->left=NULL; // makes the first nodes left stack pointer a NULL
point=head; //saves the original mem location of the head but passes it for the loop

while( strcmp(buffer,"done") != 0 ) //typing done terminates input
	point=create(point, buffer); //pass the stack pointer and return the new pointer
point->right=NULL; //puts a null at the end of the list

printf("\n\nThe list is:\n____________________\n");
read(head); //print entire list

strcpy(buffer,""); // clearing done from buffer

while( strcmp(buffer,"done") != 0)
	{

	printf("\nType 'delete' and enter a key to delete or type 'done' to end program.\n");
	get(buffer);

	if(strcmp(buffer,"delete")==0)
		{
		printf("\nEnter key to delete:\t");
		get(buffer);
		if(strcmp(head->key,buffer)==0)
			head = delete(head, buffer);
				else 
					delete(head, buffer);
		}
	}

printf("\n\nThe list is:\n____________________\n");
read(head);

return 0;
}

NODES *delete(NODES *node, char buffer[])
{

NODES *next = node->right, *prev=node->left, *head;

if(strcmp(node->key,buffer)==0) // if key is found in curr pos or at end of list
	{
	printf("key: %s is found!\n",buffer);
	strcpy(buffer,"done"); // this will end the driver

	if( node->left == NULL ) // and if node is at the begining just drop it and make the next nodes
		{
		printf("removing from beginning\n");
		next->left = NULL; 		// left pointer be NULL
		head = node->right; // making the new head of list the second node
		return(head); //then return to calling enviroment;
		}
			else if( node->right == NULL ) //BUT if the right pointer is null, this is the end of list
				{
					printf("removing from end\n");
					node=node->left; // so move back a space
					node->right=NULL;//and make the right pointer null to drop the end of list
					return(head); //then return to calling enviroment;
				}
			else //OTHERWISE we are in the middle of the list!
				{
					printf("removing from middle\n");
					//printf("PREV RT%p switchTO RT%p\n", node->left->right, node->right);
					//printf("NEXT LF%p switchTO LF%p\n", node->right->left, node->left);
					prev->right = node->right; // switching aroung the pointers 
					next->left = node->left;

					return(head); //then return to calling enviroment;
				}
	} else if(node->right != NULL)
			delete(next,buffer);
				else
					{
					printf("\nKey does not exist\nEnter new key or type 'done'\n");
					get(buffer);	
					}

}


void read(NODES *node)
{
/////////////////////////////////////////////////////
//  show all nodes function by Mathew utter
//  Compiled for GCC 4.7.2 & 4.2.1
//

//printf("key:%s\n", node->key); // print all
printf("key:%s LF%p   RT%p\n", node->key, node->left, node->right); // print all
	
node = node->right; //storing the new mem loc in node 

if(node != NULL)
	read(node);
		else
			return;
}

NODES *create(NODES *node, char buffer[])
{
/////////////////////////////////////////////////
// create node function by Mathew utter
//  Compiled for GCC 4.7.2 & 4.2.1
//
printf("\n");

NODES *point=node, *prev=node, *new; // after creation of a new node, so nothing is makde if done is entered.

printf("Enter key:\t"); //this is all done here to make sure a node isnt created and not filled
get(buffer);
if(strcmp(buffer,"done")==0) return(node); //if done is entered return to driver

new=(NODES*) malloc(sizeof(NODES));  //new = new memory address 

strcpy(new->key,buffer); //put key in node


new->right=new; //store new's location at the stack pointer in the new node
if(prev != NULL)   //just helps create that first node 
{
	prev->right=new; //puts the new nodes memloc inside the old node
	new->left=prev;
}




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
