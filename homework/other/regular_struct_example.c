#include <stdio.h>
#include <string.h>

typedef struct 
{
char name[16];
int val;

}record;

void get(record *rec);
void show(record rec);

int main(void)
{
record rec;

get(&rec);
show(rec);

return 0;
}


void get(record *rec)
{
char buffer[16];

printf("\nEnter name:\t");
fgets(buffer,16,stdin);
strcpy((*rec).name,buffer);



printf("\nEnter value:\t");
fgets(buffer,16,stdin);
(*rec).val = atoi(buffer);

printf("\n");
return;
}


void show(record rec)
{
printf("Name: %s\nValue: %d\n\n",rec.name,rec.val);
return;
}