//GREY CODE MATRIX POPULATOR

#include <iostream>
#include <cstdlib>
using namespace std;

int main (void)
{

unsigned short grid[5][5], col, row;
unsigned short cmask, rmask;
char map[5][5] = {
{'e','e','e','e','s'},
{'n','s','w','w','s'},
{'n','s','c','n','s'},
{'n','e','s','n','s'},
{'n','w','w','n','w'}
};


for( col=0U;col<5U;col++ )
  for( row=0U;row<5U;row++ )
    {
    cmask = 1U;
    rmask = 16U;

    rmask <<= row;
    cmask <<= col;

    grid[row][col] = cmask | rmask;
    }

cout << endl << "GRID GREY CODE" << endl;
for( col=0;col<5;col++ )		{
  for( row=0;row<5;row++ )
    cout << grid[row][col] << "\t";
    cout << endl;		}

cout << endl << "DIRECTION MAP" << endl;
for( col=0;col<5;col++ )		{
  for( row=0;row<5;row++ )
    cout << map[col][row] << "\t";
    cout << endl;		}

cout << endl << ";NORTH" << endl;
for( col=0;col<5;col++ )
  for( row=0;row<5;row++ )
		if ( map[col][row] == 'n' )
			cout << ":" << grid[col][row] << endl;

cout << endl << ";SOUTH" << endl;
for( col=0;col<5;col++ )
  for( row=0;row<5;row++ )
		if ( map[col][row] == 's' )
			cout << ":" << grid[col][row] << endl;

cout << endl << ";EAST" << endl;
for( col=0;col<5;col++ )
  for( row=0;row<5;row++ )
		if ( map[col][row] == 'e' )
			cout << ":" << grid[col][row] << endl;

cout << endl << ";WEST" << endl;
for( col=0;col<5;col++ )
  for( row=0;row<5;row++ )
		if ( map[col][row] == 'w' )
			cout << ":" << grid[col][row] << endl;

return 0;
}
