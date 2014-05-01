////////////////////////////
// BY MAT UTTER
// Compile with GCC 4.7.2
// finds area of trapezoids

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
printf("To find the area of all trapezoids follow these 5 rules...\n");
printf("1. Enter the coordinates where the trapezoid(s) meet the function y=f(x).\n");
printf("2. Enter the x and y seperate.\n");
printf("3. Enter the coordinates from left to right.\n\n");


char buffer[256];
int control=0, i=0, points;
	int x[100] = {2,3,5,6,8,9};
	int y[100] = {1,3,2,5,5,4};
	points = 6;

printf("Would you like to fill in default data? (y or n)\n");
gets(buffer);
		if( strcmp(buffer, "y")==0 ) control = 1;
			else { control = 0; }

if( control == 1 )
	{

	}
	else
	{
	printf("Enter x then y, type done to finish input.\n");
	while( control != 1 )
		{
		printf("x:\t");
		gets(buffer);
		if( strcmp(buffer, "done")==0 ) control = 1;
			else { x[i] = atof(buffer); }
		
		if ( control != 1 ) 
			{
			printf("y:\t");
			gets(buffer);
			if( strcmp(buffer, "done")==0 ) 
				{
				control = 1;
				printf("\"done\" detected in y, assuming 0\n");
				y[i]=0;
				} else { 
				y[i] = atof(buffer);
				}
			}
	i++;
		}
	points = i - 1;
	}

for( i=0; i<points; i++)
{
printf("(%d,%d) \t",x[i],y[i]);
}

int total_area=0;
int width, height, box, boxes=0;
int Ax, Ay, Bx, By, Cx, Cy, triangle, polys=0;
for( i=0; i<points; i++)
{

Ax=x[i];
Ay=y[i];
Bx=x[i+1];
By=y[i+1];

if( Ay != By )
{
	if( Ay > By )
	{
	Cx=Ax;
	Cy=By;
	} else {
	Cx=Bx;
	Cy=Ay;
	}
	triangle=(Ax*(By=Cy) +Bx*(Cy-Ay) +Cx*(Ay-By))/2;
	polys++;
	height = Ay;
	width = Ax - Bx;
	if( width < 0 ) width=width*-1;
	box = height * width;
	boxes++;
	total_area = total_area + box + triangle;
} else {
	height = Ay;
	width = Ax - Bx;
	if( width < 0 ) width=width*-1;
	box = height * width;
	boxes++;
	total_area = total_area + box;
}
}


printf("\n\n\tThere are %d polys\n",polys);
printf("\tThere are %d boxes\n",boxes);
printf("\tAnd the total area is %d\"\n\n",total_area);


return 0;
}
