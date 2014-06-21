//	Header file stock prices
//  T_NODE CLASS FUNCTIONS... 
//
//    T_NODE - Constructor - creates random a # data file # is user defined
//    copy_value - bubble sort container class elements by value in increasing order
//    sort_change - nested bubble sort for container class elements by day and time in increasing order
//    display_change - special 'print' function for a 'sort_chage' sortted container 
//    show_range - finds highest and lowest values of value, the container class element
//    retrieve_data - reads in data file created by constructor, burns artifact of repeated last element and skips position 0 to use in swapping (sorting) later
//    diplay - regular 'print' function for normal data
//
//
//
//	language: C++ (g++ -v 4.7.2)
//	written by: Mathew C Utter
//	Feb 2013

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#define myDAT unsigned short
using namespace std;

class T_NODE
{
/*========================================================*/
/*function members - prototypes for outlined members*/
/*this constructor must be polymorphic                    */
  public:
  template<class TYPE> // encase the .cpp uses wants something big created? stops working around 65k
  T_NODE(TYPE x)
	{
//creates a file full of sudo random data
//language: C++ (g++ -v 4.7.2)
//written by: Mathew C Utter
//April 2013
  ofstream  fp;   fp.open("data.txt");

  fp << "STOCK	VALUE	DAY	TIME" << endl;
  for (	i=0x0;i<0x3;i++ )
	  stock	+= rand() % 0x23 + 0x41;

  for (x;x!=0x0;x--){
	  day		=rand() % 0xE + 0x1; // trades happen on random days
	  value	=rand() %	0x3E7 + 0x1;// keeping prices readable
	  time	=rand() % (0x6A4-0x3A2) + 0x3A2; //time range in US 

	  fp << stock << "	"
		   << value << "	"
	  	 << day 	<< "	"
		   << time	<< "	"
		   << endl;
	  }

  fp.close();
  retrieve_data();	
  }
  
  
/*=======================================================*/
/*Inline function members*/
/*=========================================================*/
//template<typename container_TYPE>
void copy_value(void)
	{    
//bubble sort the data held in a container class (vector) BY VALUE
//language: C++ (g++ -v 4.7.2)
//written by: Mathew C Utter
//April 2013

// bubble sort, actual vector sort wasnt working 
for ( i=0x1; i<rec.size(); i++ )
	for ( x=0x1; x<rec.size()-i; x++ )
		if ( rec[x].value > rec[x+0x1].value ) {
		rec[0x0] 	= rec[x];
		rec[x] 		= rec[x+0x1];
		rec[x+0x1] 	= rec[0x0];
		}
}

void sort_change(void)
{
//double bubble sort data in container class (vector) 
//PRIMARY SORT: DAY   SECONDARY SORT: TIME
//language: C++ (g++ -v 4.7.2)
//written by: Mathew C Utter
//April 2013
for ( i=0x1; i<rec.size(); i++ )
	for ( x=0x1; x<rec.size()-i; x++ ) {
		if ( rec[x].day > rec[x+0x1].day ) {
			rec[0x0] 	= rec[x];
			rec[x] 		= rec[x+0x1];
			rec[x+0x1] 	= rec[0x0];
		}
		if( rec[x].day == rec[x+0x1].day && rec[x].time > rec[x+0x1].time ) {
			rec[0x0] 	= rec[x];
			rec[x] 		= rec[x+0x1];
			rec[x+0x1] 	= rec[0x0];
		}
	}
}


void display_change(void)
  {
//special display function for showing change after a sort_change
//shows change between each transation
//language: C++ (g++ -v 4.7.2)
//written by: Mathew C Utter
//April 2013
  cout << endl << "Record Elements found:	" 
       << rec.size()-0x1 << endl
       << "STOCK	DAY	TIME	VALUE	CHANGE	RECORD" << endl;

  for ( i=0x1; i!=rec.size(); ++i){
    cout<< rec[i].stock << "	"
		    << rec[i].day << "	"
		    << rec[i].time 	<< "	"
				<< rec[i].value	<< "	";
		if ( i == 0x1 ) 
			cout<< "###" << "###" << "	  #" << i << endl;
		else
		if ( rec[i].value < rec[i-0x1].value )
			cout<< "-" << rec[i-0x1].value - rec[i].value << "	  #" << i << endl;
		else
			cout<< "+" << rec[i].value - rec[i-0x1].value << "	  #" << i << endl;
    }
  }

void show_range(void)
{
//finds the lowest and highest values contained within some element of containers
//language: C++ (g++ -v 4.7.2)
//written by: Mathew C Utter
//April 2013
myDAT high=0, low=999;
for ( i=0x1; i<rec.size(); i++ ) {
	if ( rec[i].value > rec[i+0x1].value && rec[i].value > high ) high = rec[i].value;
	if ( rec[i].value < rec[i+0x1].value && rec[i].value < low )  low  = rec[i].value;
}

cout << endl << "Lowest stock value:	" << low << endl
		 << "Highest stock value:	" << high << endl << endl;
}

void retrieve_data(void)
  {
//reads a data file and places data into the containers by pushing each
//new container class into the back of the container structure (vector)
//language: C++ (g++ -v 4.7.2)
//written by: Mathew C Utter
//April 2013
//
// IMPORTANT :
// position 0 is left unused so that the sorting functions have
// a location for swapping container elements without creating a new
// container class

  ifstream  fp;   fp.open("data.txt");
  while( !fp.eof() ){
    getline (fp,line,'\n');
    stringstream ss(line);
	  ss >> stock >> value >> day >> time;  
    rec.push_back({stock,value,day,time}); 
 	  }
  fp.close();
  // burning last element
  it = rec.end();
  rec.erase(it);
  }

void display(void)
  {
//regular data display function, shows each element of the container class
//except position 0 which is used for swaping
//language: C++ (g++ -v 4.7.2)
//written by: Mathew C Utter
//April 2013
  cout << endl << "Record Elements found:	" 
       << rec.size()-0x1 << endl
       << "STOCK	DAY	TIME	VALUE	RECORD" << endl;

  for ( i=0x1; i!=rec.size(); ++i){
     cout << rec[i].stock << "	"
		      << rec[i].day << "	"
		      << rec[i].time 	<< "	"
		      << rec[i].value	<< "	  #" << i << endl;
    }
  }

/*=========================================================*/
/*data members of PUBLIC SECTION */
class NODE
{
public:
string stock;
myDAT value, day, time;
};
vector<NODE> rec;
/*END OF PUBLIC SECTION*/
/*=========================================================*/
/*data members of PRIVATE section*/
private:
myDAT value, day, time, i, x;
string stock, line;
vector<NODE>::iterator it;
/*=========================================================*/
}; // END CLASS
