///////////////////////////////////////////////////////////////////////
//  payroll revision by Mathew C Utter
//  9 - 17 - 2012
//  some functions, and general scope of program is an adaptation from
//  Ron Sarner's class handouts and example programs
//
//  payroll small program that reads a text file into a struct and 
//  does math based on those double values
//  it makes new records based on old data
//  but always does the same calculation
//  "gross = hours * rate"
//  "deductions = rate + fica + medi + fed + state"
//  "net = gross - ( gross * deductions )"
//  
///////////////////////////////////////////////////////////////////////
//  REVISION 2 ON 9 - 28 - 2012  IMPORTANT******************
//  ONLY TESTED ON TCC for Windows
///////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ARG_SIZE 35

typedef struct 
{
char name[7];
double value;
}polling_struct;

void scan_records(polling_struct polling_rec[ARG_SIZE]);
void make_blank(polling_struct polling_rec[ARG_SIZE]);
void edit_records(polling_struct polling_rec[ARG_SIZE]);
void do_changes(polling_struct polling_rec[ARG_SIZE], int n);
void calc_net(polling_struct polling_rec[ARG_SIZE], int n);
void print_totals(polling_struct polling_rec[ARG_SIZE]);
void print_bar(void);
void write_to_file(polling_struct polling_rec[ARG_SIZE]);
void help(void);

int main(void)
{
printf("IN OBJ: main<-----\n");
int n=1;
char buffer[1];
polling_struct polling_rec[ARG_SIZE];

help();
while( n == 1 )
  {
  fgets(buffer, 10, stdin);
  if(strcmp(buffer,"help\n")==0) help();
  if(strcmp(buffer,"scan\n")==0) scan_records(polling_rec);
  if(strcmp(buffer,"edit\n")==0) edit_records(polling_rec);
  if(strcmp(buffer,"show\n")==0) print_totals(polling_rec);
  if(strcmp(buffer,"calc\n")==0) calc_net(polling_rec,n);
  if(strcmp(buffer,"save\n")==0) write_to_file(polling_rec);
  if(strcmp(buffer,"make\n")==0) make_blank(polling_rec);
  if(strcmp(buffer,"exit\n")==0) n=0;
  }

return 0;
}

void help(void)
{
printf("This program calculates the payrole of an individual\n");
printf("Here are the following functions:\n");
printf("\t'scan' - will scan for payrole.text\n");
printf("\t'show' - displays the current record\n");
printf("\t'edit' - will edit data for the individual\n");
printf("\t'calc' - will calculate the net pay\n");
printf("\t'save' - will output the data to payrole_output.txt\n");
printf("\t'make' - will create a blank payrole.txt\n");
printf("\t'exit' - will end the program\n");
printf("type 'help' at any time to display this message again\n\n");
return;
}



void scan_records(polling_struct polling_rec[ARG_SIZE])
{
printf("IN OBJ: scan_records<-----\n");
int i=0;
double value_buffer;
char c;

printf("Scanning...\t");
FILE *fp = fopen("payroll.txt", "r");
if(fp == NULL) 
  {
  printf("\t[FAIL]\n");
  fclose(fp);
  }
  else 
  { 
  printf("\t[ OK ]\n");
  }

while ( c != EOF )
  {
  for(i=0; i!=8; i++)
    {
    fscanf(fp,"%s %lf\r\n", polling_rec[i].name, &value_buffer);  
    polling_rec[i].value=value_buffer;
    }
  c = getc(fp);
  }

fclose(fp);
print_totals(polling_rec);
return;
}

void make_blank(polling_struct polling_rec[ARG_SIZE])
{
printf("IN OBJ: make_blank<-----\n");
double hours, rate, gross, fica, medi, fed, state, net;
hours=0.0, rate=0.0, gross=0.0, fica=6.2, medi=1.45, fed=15.0, state=5.0, net=0.0;
FILE *fp = fopen("payroll.txt", "w");

printf("Creating file...\t");
if(fp != NULL) printf("[ OK ]\n");
  else printf("[FAIL]\n");

fprintf(fp, "hours %0.2lf\n", hours);
fprintf(fp, "rate %0.2lf\n", rate);
fprintf(fp, "gross %.02lf\n", gross);
fprintf(fp, "fica %0.2lf\n", fica);
fprintf(fp, "medi %0.2lf\n", medi);
fprintf(fp, "fed %0.2lf\n", fed);
fprintf(fp, "state %0.2lf\n", state);
fprintf(fp, "net %0.2lf\n", net);

printf("Data insert...\t");
printf("\t[ OK ]\n");
 
fclose(fp);
scan_records(polling_rec);
return;
}

void edit_records(polling_struct polling_rec[ARG_SIZE])
{
printf("IN OBJ: edit_records<-----\n");
char edit_this[1];
int n=1;

while(n==1)
  {
  print_totals(polling_rec);
  printf("Which value would you like to update? (type none to exit)\n");
  scanf("%s", edit_this);
  
  if(strcmp(edit_this,"none")==0) 
    {
    n=3;
    } else {
    for(int i=0; i!=8; i++)
      {
      if(strcmp(edit_this,polling_rec[i].name) == 0) 
        {
        n=i;
        print_bar();
        printf("%s was found in record %d ", edit_this, n);
        do_changes(polling_rec,n);
        n=1;
        break;
        } else {
        n=1;
        }
      }
  if(n==1 && strcmp(edit_this,"none")!=0) printf("No match found...\n"); 
    }
  }
return;
}

void do_changes(polling_struct polling_rec[ARG_SIZE], int n)
{
printf("IN OBJ: do_changes<-----\n");
double value_buffer;
printf("and is currently set to %4.2lf \n\t Enter new value.\t",  polling_rec[n].value);
scanf("%lf", &value_buffer);

polling_rec[n].value = value_buffer;  
return;
}

void calc_net(polling_struct polling_rec[ARG_SIZE], int n)
{
printf("IN OBJ: calc_net<-----\n");
double hour, rate, gross, fica, medi, fed, state, net, total;
int i=0;

hour = polling_rec[0].value;
rate = polling_rec[1].value;
gross = polling_rec[2].value;
fica = polling_rec[3].value;
medi = polling_rec[4].value;
fed = polling_rec[5].value;
state = polling_rec[6].value;
net = polling_rec[7].value;

gross = hour * rate;
total = (fica + medi + fed + state)/100;
net = gross - gross * total;

polling_rec[2].value = gross;
polling_rec[7].value = net;

return;
}

void print_totals(polling_struct polling_rec[ARG_SIZE])
{
printf("IN OBJ: print_totals<-----\n");
int i;

printf("\nTHE FOLLOWING RECORD WILL BE WRITEN TO FILE\n");
print_bar();

for (i=0; i!=8; i++)  printf("%s \t",polling_rec[i].name);
printf("\n");
for (i=0; i!=8; i++)  printf("%4.2lf \t",polling_rec[i].value);
printf("\n");
print_bar();
return;
}

void write_to_file(polling_struct polling_rec[ARG_SIZE])
{
printf("IN OBJ: write_to_file<-----\n");
FILE *fp = fopen("payroll_output.txt", "w"); //will only over write data

printf("Opening file...\t\t");
if(fp == NULL)
  {
  printf("[FAIL]\n");
  }else{
  printf("[ OK ]\n");
  }
  
for(int i=0;i!=8;i++)
  {
  fprintf(fp, "%s %lf\r\n", polling_rec[i].name, polling_rec[i].value);
  }

printf("Writing data...\t\t");
printf("[ OK ]\n");
fclose(fp);

printf("Closing file...\t\t");
printf("[ OK ]\n");
return;
}

void print_bar(void)
  {
  for(int i=0; i!=80; i++) printf("%c",220); printf("\n");
  return;
  }
