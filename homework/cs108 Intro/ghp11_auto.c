////////////////////////////////////////////////////////////////////////////////////////////////////////
//  BY MATHEW C UTTER
//  GHP 11 structure_variables_auto_t
//  11/30/2012
//		
//  Define a structure type auto_t to represent an automobile. 
//  Include components for the make and model (strings),
//  the odometer reading, the date of manufacture, the date 
//  of purchase, the gas tank capacity (in gallons), and the current
//  fuel level	(in gallons). Main should call a function that prompts
//  the user for data to fill all components of the structure, and a
//  second function that displays the values of all of the components.
//  The purpose of this program is to ensure that you can	create and access a struct.
//
//  Compiled for GCC 4.7.2 & 4.2.1
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 16

typedef struct
{
char make[SIZE], model[SIZE];
int odom, datem, datep;
double fuel_cap, fuel_lev; // my honda has an 11.5 gallon tank so? assumed double
} auto_t;

void get_data(auto_t *car); // assume a regular struct and not an array
void show(auto_t car);

int main(void)
{
auto_t car;
printf("This program takes input and sticks it into a struct\n");
printf("It handles '. /\\' symbols in the date inputs\nand ',' in the integer(miles) field. \n");
printf("By handles I mean converts them into integers.\n\n\n");
printf("Enter car data below... \n");
get_data(&car); //passing regular struct by ref
show(car);

return 0;
}

void get_data(auto_t *car)
{
////////////////////////////////////////////////////////////////////////////////////////////////////////
//  BY MATHEW C UTTER
//  GHP 11 get_data function & string parsing
//  11/30/2012
//  

int i;
char *var_names[]={"Car Make","Car Model","Odometer","Manufactured","Purchased","Fuel capacity","Fuel level"};
char buffer[SIZE], container[SIZE], *tok, key[]={". /\\"};
strcpy(container,"\0"); // in gcc 4.2.1 this must be seeded a value or is behaves weird

for( i=0;i<7;i++ )
	{
	printf("\n\t%s:\t",var_names[i]);
	fgets(buffer,SIZE,stdin);
	buffer[strlen(buffer)-1] = 0;

	switch ( i )
		{
		case 0:
			strcpy((*car).make,buffer);	break;

		case 1:
			strcpy((*car).model,buffer);	break;

		case 2:
			tok = strtok (buffer,",");
			while (tok != NULL)
			{
				strcat(container,tok);
 				tok = strtok (NULL, ",");
  			}
			(*car).odom = atoi(container);
			strcpy(container,"\0");

			break;
			
		case 3:
			tok = strtok (buffer,". /\\"); //doing all this token stuff, assuming if it was an array of structs, or a linked list, values of dates could be used to sort by.
			while (tok != NULL)
			{
				strcat(container,tok);
 				tok = strtok (NULL, ". /\\");
  			}
			(*car).datem=atoi(container);
			strcpy(container,"\0");
			break;

		case 4:
			tok = strtok (buffer,". /\\");
			while (tok != NULL)
			{
				strcat(container,tok);
 				tok = strtok (NULL, ". /\\");
  			}
			(*car).datep=atoi(container);
			strcpy(container,"\0");
			break;

		case 5:
			(*car).fuel_cap=atol(buffer);
			break;
		case 6:
			(*car).fuel_lev=atol(buffer);
			break;
		}
	}
printf("\n\tStruct filled!\n");
return;
}

void show(auto_t car)
{
////////////////////////////////////////////////////////////////////////////////////////////////////////
//  BY MATHEW C UTTER
//  GHP 11 show function
//  11/30/2012
printf("\n  Showing Data!");
printf("\n\n  Car Make:\t%s\n  Car Model:\t%s\n  Odometer:\t%d\n  Manufactured:\t%d\n",car.make,car.model,car.odom,car.datem);
printf("  Purchased:\t%d\n  Fuel Cap:\t%0.2lf\n  Current Fuel:\t%0.2lf\n\n",car.datep,car.fuel_cap,car.fuel_lev);

return;
}