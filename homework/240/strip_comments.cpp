//GHP3 worst program I ever wrote ( didnt have enough time )
//language: C++ (g++ -v 4.7.2)
//written by: Mathew C Utter
//March 2013
//meeting the specifications of #7 on Page 249
//from Page 249 "Write a program that reads a file containing a C++ program
//and produces a file with all comments stripped from the program."
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string strip(string hold, bool &inblock);
string get_good_name(void);

int main(void)
{
string name, tline;
bool inblock = false;
cout<< endl << "This program removes comments from C++ source files (.cpp)." << endl
		<< "Please include the file extension in both Input and Output filenames." << endl;
cout << "Enter INPUT filename..."<<endl;
name = get_good_name();
ifstream  fp;  fp.open (name.c_str()); 
cout << "Enter OUTPUT filename..."<<endl;
getline(cin,name);
ofstream tfp; tfp.open (name.c_str());

cout << endl << "Making commentless copy..." << endl << "working";
    while ( fp.good() )
    {
      getline (fp,tline,'\n');
			tline = strip(tline, inblock);
			tfp << tline;
    }
cout << " Done!" << endl << endl;
if(fp.is_open() || tfp.is_open())
	{
	 fp.close();
	tfp.close();
	}
return 0x0;
}

string get_good_name(void)
{
	// GET GOOD NAME gets a filename that exists
	//language: C++ (g++ -v 4.7.2)
	//written by: Mathew C Utter
	//Feb 2013
string name;
cout << "Enter name of file  :";
getline (cin,name);

ifstream  fp;  fp.open (name.c_str()); 
if ( !fp.is_open() )
	{
	cout << "Bad filename! Try again..." << endl;
	fp.close();
	name = get_good_name();
	}

fp.close();
return name;
}


string strip(string l, bool &inblock)
{
	//strips off comments from C++ code. ONLY when they follow my format
	//language: C++ (g++ -v 4.7.2)
	//written by: Mathew C Utter
	//Feb 2013
bool Lprot;
unsigned skip, pos, next, size = l.length();
string key0("//"), key1("/*"), key2("*/"), avoid0(";"), avoid1("\"//\""), avoid2("\"/*\""); 
if ( inblock == true )
  if ( l.find(key2) != string::npos ) {
    l.erase(0x0,l.find(key2)+0x2);
    inblock = false; }
  else
    l.erase(0x0,string::npos);    

if ( l.find(avoid1) != string::npos || l.find(avoid2) != string::npos )
  Lprot = true; else Lprot = false;

if ( l.find(key2) != string::npos && l.find(key1) != string::npos && Lprot == false )
      l.erase(l.find(key1),l.find(key2)+0x2);
    else if ( l.find(key2) == string::npos && l.find(key1) != string::npos && Lprot == false ) {
      l.erase(l.find(key1),string::npos);
      inblock = true; }    

if ( inblock == false ) 
  {
  if ( l.find(key0) != string::npos && Lprot == false )
    if ( l.find(key0,l.rfind(";")) != string::npos )
      l.erase(l.find(key0,l.rfind(";")));
    else
      l.erase(l.find(key0));
  }
if (l.length() > 0)
	l.append("\n");
cout << ".";
return l;
}
