#include <stdio.h>

int main()
{
int pull_num;
double emitted, odometer;

printf("enter pollutent num:  ");
scanf("%d",&pull_num);

printf("enter grames emitted num:  ");
scanf("%lf",&emitted);

printf("enter odometer num:  ");
scanf("%lf",&odometer);

//////////////////////////////
// START OF SWITCH BLOCK
switch (pull_num){

  case 1: 
    if(emitted<3.4 &&  odometer<50000)
      printf("Thats in the bounds\n");
    else
      printf("That exceeds the permitted level of 3.4!!\n");

    if(emitted<4.2 && odometer<100000)
      printf("Thats in the bounds\n");
    else
      printf("That exceeds the permitted level of 4.2!!\n");



  break;

  case 2: 
    if(emitted>.31 && emitted<.39 && odometer<100000)
      printf("Thats in the bounds\n");
    else
      printf("That exceeds the permitted level!!\n");
  break;

  case 3: 
    if(emitted>.4 && emitted<.5 && odometer<100000)
      printf("Thats in the bounds\n");
    else
      printf("That exceeds the permitted level!!\n");
  break;

  case 4: 
    if(emitted>.25 && emitted<.31 && odometer<100000)
      printf("Thats in the bounds\n");
    else
      printf("That exceeds the permitted level!!\n");
  break;

}
// END OF SWITCH BLOCK
//////////////////////////////
return 0;
}
