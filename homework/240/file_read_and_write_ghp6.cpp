// GHP6 trading stocks!
// by Mathew C Utter 
// Compiled for G++ (v 4.2.1)
// March, 2013
// PROBLEM STATEMENT: ( #31 pg 583 )
// The investment company of pickum & loozem has been recording the trading price of a particular stock over 15-day period. 
// *write a program that reads these prices and stores them in a sequential container
// *sort them into increasing order
// *find and display the TRADING RANGE (LOW vs. HI prices recorded)
// *a sequence that shows how much CHANGE in prices over TIME
#include <iostream>
#include "test.h"

using namespace std;

int main(void)
{
cout << "Creating random rec for US Stock Exchange..." << endl;
cout << "Enter how many transactions to generate: ";
int num; cin >> num;
T_NODE ALPHA(num);
ALPHA.display();

cout << endl << "Sorting records by increasing order...";
ALPHA.copy_value();
ALPHA.display();

cout << endl << "Sorting records by sequence, showing change between transaction...";
ALPHA.sort_change();
ALPHA.display_change();

cout << endl << "Displaying final trading range...";
ALPHA.show_range();

cout << endl << endl;
return 0;
}
