// GHP5 Palindrome, uses stack and queue to test for palindrome!
// by Mathew C Utter 
// Compiled for G++ (v 4.2.1)
// March, 2013
#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

int main(void)
{
queue<char> my_q;
stack<char> my_s;
string word;
int i;

cout << endl << "Enter:\t";
cin  >> word;

for ( i=0; i!=word.length(); i++ ) {
my_q.push(word[i]);
my_s.push(word[i]);
}
cout << "\t";

while( !my_s.empty() ){
  if ( my_q.front() != my_s.top() ) {
    cout << "That is not a palindrome!" << endl;
    return 0;
    }  
  my_q.pop();
  my_s.pop();
  }

cout << "That is a palindrome!" << endl << endl;
return 0;
}
