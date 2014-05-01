/////////////////////////////////
//  BY MAT UTTER
//  Compile with GCC 4.7.2
//  grocery store
//  chapter 10, problem 8
//  from Hanley 7th Edition
/////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define BF 20
#define ITM 50

// example source data .txt (not including paranthesis)
//  (catagory)	(name)	(cost)	(month)	(year)	(meta_data)	
//    meaf			  roast	 233c			  11			12				f	
//  (representation inside struct)
//    meaf       roast   2.33         11        12         f
//  (so formatting is required to for IO)

typedef struct
{
char cat[5], name[10], meta[5];
double cost;
int month, year, id;
}inventory;

void get_command(char buffer[BF]);
void help(void);
void make_default(char buffer[BF]);
void scan(char buffer[BF]);
int   copy_to_struct(char buffer[BF], inventory item[ITM]);
void show(int data_available, inventory item[ITM]);
void edit(char buffer[BF], inventory item[ITM]);
void save(int data_available, char buffer[BF], inventory item[ITM]);

int main(void)
{
//printf("\tIN OBJ: main <---\n");

inventory item[ITM];
char buffer[BF], *c;
int data_available=0;

while(strcmp(buffer,"done") != 0)
	{
	printf("\n\nWhat would you like to do? ('help' for more info)\n");
	printf("| show | scan | make_default | edit | save | help | done |\n");
	get_command(buffer);
	c = strchr(buffer,' ');
	if(c != NULL) printf("NO COMPOUND COMMANDS!\n");

	if(strcmp(buffer,"help") == 0) help();
	if(strcmp(buffer,"make_default") == 0) make_default(buffer);
	if(strcmp(buffer,"scan") == 0) 
		{
		scan(buffer);
		data_available = copy_to_struct(buffer, item);
		show(data_available, item);
		}
	if(strcmp(buffer,"show") == 0 && data_available > 0)
			show(data_available, item);
	if(strcmp(buffer,"edit") == 0) edit(buffer, item);
	if(strcmp(buffer,"save") == 0) save(data_available, buffer, item);
	}
return 0;
}


void get_command(char buffer[BF])
{
//printf("\tIN OBJ: get_command <---\n");

fgets(buffer, BF, stdin);
buffer[strlen(buffer)-1] = 0;

return;
}

void save(int data_available, char buffer[BF], inventory item[ITM])
{
//printf("\tIN OBJ: save <---\n");

int i=0;

printf("What would you like to save the file as? (.txt will be added)");
get_command(buffer);
strcat(buffer,".txt");

FILE *fp = fopen(buffer, "w");

for( i=0;i<data_available; i++)
	fprintf(fp,"%s %s %0.0lfC %d %d  %s\n", item[i].cat, item[i].name, item[i].cost*100 ,item[i].month,item[i].year,item[i].meta);

printf("%s created!\n", buffer);
fclose(fp);
return;
}

void edit(char buffer[BF], inventory item[ITM])
{
//printf("\tIN OBJ: edit <---\n");

int id;
double cost;

printf("Enter item ID to edit item data:");
get_command(buffer);
id = atoi(buffer);

printf("\tDisplaying item ID: %d\n", id);
printf("\n\tID:%d\t%s\t%s\t$%.2lf\t%d/%d\t%s\n",item[id].id, item[id].cat, item[id].name, item[id].cost ,item[id].month,item[id].year,item[id].meta);


printf("Data row to edit: (catagory, name, cost, date, meta, OR 'end' to stop.)\n");
get_command(buffer);

if(strcmp(buffer,"end") != 0)
	{
	if(strcmp(buffer,"catagory") == 0)
		{
		printf("Enter new catagory: (meaf, canf, prod, dary, nonf)\t");
		get_command(buffer);
		strcpy(item[id].cat,buffer);
		}
	if(strcmp(buffer,"name") == 0)
		{
		printf("Enter new name:\t");
		get_command(buffer);
		strcpy(item[id].name,buffer);
		}
	if(strcmp(buffer,"cost") == 0)
		{
		printf("Enter new cost: (end cent value in C)\t");
		get_command(buffer);
		buffer[strlen(buffer)-1] = 0;
		get_command(buffer);
		cost = atol(buffer)/100.0;
		item[id].cost = cost;
		}
	if(strcmp(buffer,"date") == 0)
		{
		printf("Enter new month:\t");
		get_command(buffer);
		item[id].month = atoi(buffer);
		printf("Enter new year:");
		get_command(buffer);
		item[id].year = atoi(buffer);
		}
	if(strcmp(buffer,"meta") == 0)
		{
		printf("Enter new meta data:\t");
		get_command(buffer);
		strcpy(item[id].meta,buffer);
		}
	}

printf("\tDisplaying new item ID: %d\n", id);
printf("\n\tID:%d\t%s\t$%.2lf\t%d/%d\t%s\n",item[id].id, item[id].name, item[id].cost ,item[id].month,item[id].year,item[id].meta);

return;
}

void show(int data_available, inventory item[ITM])
{
//printf("\tIN OBJ: show <---\n");
int i=data_available, x=0;

for(x=0;x<i;x++)
	{
	printf("\n\tID:%d\t%s\t$%.2lf\t",item[x].id, item[x].name, item[x].cost);
	if(strcmp(item[x].cat,"meaf") == 0)
		{
		printf("EXPIRE:%d/%d\t", item[x].month, item[x].year);
		if(item[x].meta[strlen(item[x].meta-1)] == 'R')
			printf("Red\t");
				else if(item[x].meta[strlen(item[x].meta-1)] == 'F')
					printf("Fish\t");
						else printf("Poultry\t");
			printf("Meat Department.\n");
		}
	if(strcmp(item[x].cat,"canf") == 0)
		{
		printf("EXPIRE:%d/%d\t", item[x].month, item[x].year);
		printf("Canned\tSide %c  ", item[x].meta[strlen(item[x].meta)-1]);
		printf("Aisle %*.*s.\n", 1, 2, item[x].meta);
		}
	if(strcmp(item[x].cat,"prod") == 0)
		{
		printf("RECIEVE:%d/%d\t", item[x].month, item[x].year);
		if(item[x].meta[strlen(item[x].meta-1)] == 'V')
			printf("Vegi\t");
				else
					printf("Fruit");
		printf("Prod Department.\n");
		}
	if(strcmp(item[x].cat,"dary") == 0)
		{
		printf("EXPIRE:%d/%d\t", item[x].month, item[x].year);
		printf("Dairy\tDiary Department.\n");
		}
	if(strcmp(item[x].cat,"nonf") == 0)
		{
		printf("EXPIRE:%d/%d\t", item[x].month, item[x].year);
		if( item[x].meta[strlen(item[x].meta-1)] == 'C' )
				printf("Cleaning\t");
					else if( item[x].meta[strlen(item[x].meta-1)] == 'P' )
						printf("Pharmacy\t");
							else
								printf("Other\t");

		printf("Side %c  ", item[x].meta[strlen(item[x].meta)-2]);
		printf("Aisle %*.*s.\n", 1, 2, item[x].meta);
		}
	}
return;
}

void make_default(char buffer[BF])
{
//printf("\tIN OBJ: make_default <---\n");
FILE *fp = fopen("default.txt", "w");
if(fp == NULL ) printf("error\n");
	else printf("default file created...\n");

fprintf(fp,"meaf steak 233C 11 2012 R\n");
fprintf(fp,"canf corn 89C 11 2000 12B\n");
fprintf(fp,"canf beens 99C 11 2012 12A\n");
fprintf(fp,"meaf pork 199C 1 2013 R\n");
fprintf(fp,"meaf tuna ITMC 3 2013 F\n");
fprintf(fp,"meaf turkey 1BFC 1 2013 P\n");
fprintf(fp,"prod potato 69C 11 2013 V\n");
fprintf(fp,"dary milk 499C 12 2012 d\n");
fprintf(fp,"nonf bleach 299C 12 2014 11BC\n");

fclose(fp);

strcpy(buffer,"default");
scan(buffer);

return;
}

void scan(char buffer[BF])
{
//printf("\tIN OBJ: scan <---\n");
if(strcmp(buffer,"default") != 0)
	{
	printf("Enter file to be scanned (.txt will be added):\n");
	get_command(buffer);
	}
strcat(buffer,".txt");
return;
}

int copy_to_struct(char buffer[BF], inventory item[ITM])
{
//printf("\tIN OBJ: copy_to_struct <---\n");
int i=0,x=0;
char cost_buffer[10], c;
double cost;

printf("scanning %s...\n",buffer);
FILE *fp = fopen(buffer, "r");
	if(fp == NULL) printf("fail");
while ( c != EOF )
  {
	fscanf(fp,"%s %s %s %d %d %s", item[i].cat, item[i].name, cost_buffer, &item[i].month, &item[i].year, item[i].meta);

	cost_buffer[strlen(cost_buffer)-1] = 0;
	cost = atol(cost_buffer)/100.0;
	item[i].cost = cost;
	item[i].id = i;

	c = getc(fp);
	if( c != EOF ) i++;
  }
fclose(fp);

return i;
}

void help(void)
{
//printf("\tIN OBJ: help <---\n");
printf(" Enter 'scan' to load inventory data from a file.\n");
printf(" Enter 'make default' to create a file with a set of test data.\n");
printf(" Enter 'edit' to make changes to scanned data.\n");
printf(" Enter 'save' to create an 'output.txt' record of long form inventory data.\n");
printf(" Enter 'show' to show all data in the struct.\n");
printf(" Entering 'done' in the 'get_command' obj will terminate the program.\n");
return;
}