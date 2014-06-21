/////////////////////////////////////////////////////////
//Mathew C Utter GHP_down_payment.c
//By me for Comp Fundamentals
// 9 / 20 / 2012
//
////payment = (i*P)/(1-(1+i)^-n)
//
//compiled with TCC & GCC (using -lm argument)
//////////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>


void print_intro(void); //prints a small intro
void print_bar(void); //prints a line of bars (probably splits into a second like when your resolution isnt 1800x1200, trying to figure out how to grab the screen res #
double do_calculation(double arg1, double arg2, double num_payments); // the function that does the math


void print_intro(void)
{
print_bar();
printf("Welcome to Mat's Monthly Car Payment Program!\n");
print_bar();
return;
}

void print_bar(void)
  {
  int i;
  for(i=0; i!=80; i++) printf("%c",220); printf("\n"); 
  return;
  }

int main(void)
{
print_intro();

double amt_borrowed, ann_interest, num_payments, result;

printf("Enter amount borrowed:\t\t$");
scanf("%lf", &amt_borrowed);
printf("\nEnter the annual interest:\t%%");
scanf("%lf", &ann_interest);
printf("\nEnter the number of payments:\t ");
scanf("%lf", &num_payments);

result = do_calculation(amt_borrowed, ann_interest, num_payments); //passing the scnaf's and pulling the result

print_bar();
printf("Monthly payment are:\t\t$%5.2lf\n", result);
print_bar();
return 0;
}

double do_calculation(double amt_borrowed, double ann_interest, double num_payments)
{
double P, i, n, argc, argb, result;
P = amt_borrowed;
i = (ann_interest/12)/100;
n = num_payments;

argc = 1+i;
argb = n*-1;

result = pow(argc, argb);
result = (i*P)/(1-result);

return result;
}
