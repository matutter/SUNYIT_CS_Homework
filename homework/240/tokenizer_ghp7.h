//	header file for ghp7 Hash strings! 
//  TK_STORE CLASS FUNCTIONS... 
//  
//  TK_STORE - gets input with getline and calls the token function
//  cut_tokens - uses string stream sstream to place each token in a vector checks for < 15 == true
//  store - will do the algorithme for hashing, and call emplace
//  emplace - checks to see if store found a spot to place the token or place++ and recurse!
//  show - shows the string array hct which is hach container, arrays are containers! 
//
//	language: C++ (g++ -v 4.7.2)
//	written by: Mathew C Utter
//	May 2013
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
using namespace std;

class TK_STORE
{
/*========================================================*/
/*CONSTRUCTOR*/
  public:
  TK_STORE()
	{
  //just gets some input & calls next step
  //language: C++ (g++ -v 4.7.2)
  //written by: Mathew C Utter
  //April 2013
  cout<< "Enter words to be hashed and stored (max words 15)"
      << endl << "\t* ENTER WORDS IN ONE LINE *" << endl;
  getline(cin,buffer);
  cut_tokens();
  }
/*=======================================================*/

void cut_tokens(void)
	{    
  //cuts a string into multiple tokens, loops because its a  stream
  //language: C++ (g++ -v 4.7.2)
  //written by: Mathew C Utter
  //April 2013
  istringstream ss(buffer);
  copy(	istream_iterator<string>(ss),             //it for stream token start
    istream_iterator<string>(),                   // default it is end
    back_inserter<vector<string> > (token) );     // insert it is of type vector<string>
  if( token.size() > 15 ) 
    { cout<<endl<<"too many words entered: 15 is the defined limit" << endl;
    throw;
    }
}

void store(void)
	{    
  //algorithme for storing string tokens into  the hash by calling emplace
  //language: C++ (g++ -v 4.7.2)
  //written by: Mathew C Utter
  //April 2013
  fill_n(hct, 0x17, " ");
  for(vector<string>::const_iterator it = token.begin();
    it != token.end();
    ++it){
      i = ((*it)[0x0]+(*it)[string::npos-0x1])%0x17;  //"hashing" algorithme
      emplace(*it,i,hct);                             //store it @ i of hct
		}
}

void emplace(string word, int spot, string hct[23])
{
//actually assigns tokens to hash container and finds suitible empty spots
if( hct[spot][0] != ' ' )
	emplace(word, spot+0x1, hct);
else
	hct[spot] = word;
return;
}

void show(void) //by mat april 2013
{ cout<<endl<<"\t  Displaying stored hash data..."<< endl
      <<"\t* SPACES ARE EMPTY ELEMENTS *"<<endl;

  for( i=0x0;i<0x17;i++ )
  	cout<< hct[i] << " ";
  cout<< endl<<endl;
}

void find(string args)
{
i=0;
bool found = false;
spot = (args[0x0]+args[string::npos-0x1])%0x17;  
do{
  if( hct[spot] != args ){
    spot++;i++;
    if( spot>=0x17 ) spot = 0x0;
  }
  else{
    found = true;
    cout<< "\t* "<< args 
        << " found @" << spot << endl;
   }
}while(!found && i < 0x17);
}

/*data members*/
public:
string hct[0x17]; // dont need to get fancy
private:
int spot, i;
vector<string> token;
string buffer, word;
};
