#include <iostream>
#include <string>
#include <sstream> //used to cut actual tokens
#include <iterator> //iterators for making tokenss in the form of vectors
#include <vector>
#include <iomanip> // necessary for 'cout' padding
using namespace std;

void store(string word, int point, string hct[23])
{
if( hct[point][0] != 0x0 )
store(word, point+0x1, hct);
else
hct[point] = word;
return;
}

int main(void)
{
int i, point;
string buffer, hct[0x17]; // dont need to get fancy
fill_n(hct, 0x17, 0x0);//I would suggest not using hex just use regular int 0x17 is 23
  


cout<< "Enter words to be hashed and stored (max words 15)"
    << endl;
getline(cin,buffer);

istringstream ss(buffer);
vector<string> tokens; // it is short for iterator
copy(	istream_iterator<string>(ss), //it for stream tokens start
istream_iterator<string>(), // default it is end
back_inserter<vector<string> > (tokens) ); // insert it is of type vector<string> 

for(vector<string>::const_iterator it = tokens.begin();
it != tokens.end();
++it){
i = ((*it)[0x0]+(*it)[string::npos-0x1])%0x17;//"hct" algorithme
store(*it,i,hct); //store it @ i of hct
}

for( i=0x0;i<0x17;i++ )
cout<< "hash[" << setfill(' ') << setw(2) << i <<"]\t"
    << hct[i] << endl; //use of 'cout' padding


return 0;
}
