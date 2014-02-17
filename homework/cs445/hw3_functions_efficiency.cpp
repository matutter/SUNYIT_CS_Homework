// hw2 (officially hw3)
// can be used with big.txt, file.txt, and textfile
// the filenames will be hardcoded 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "profile.h"
//fread/read, fwrite/write, fopen/open, fclose/close
#define sm_buf 1024
#define lg_buf 4096

using namespace std;
int main(int argc, char const *argv[])
{
	char fname[255] = "textfile";
	operation profile[4];
	
	init(profile, fname);	//already had this written
	do_fwrite	(profile,1);
	do_fopen	(profile,0);
	do_fread	(profile,2);
	do_fclose	(profile,3);


	cout << endl << "frwite/write buffer size " << BUFSIZ << endl;
	cout << "op \t\t cycles" << endl;
	cout << profile[1].op << "" << profile[1].cycles << endl;
	cout << profile[0].op << "" << profile[0].cycles << endl;
	cout << profile[2].op << "" << profile[2].cycles << endl;
	cout << profile[3].op << "" << profile[3].cycles << endl << endl;

	ifstream inf	(fname,ifstream::in);
	ofstream ouf (fname,ofstream::out);
	const char s[BUFSIZ] = "This is a random text file used as\nan example\n\nof a file\nfor \n\nprograms to\n\n\n";
	char buf[BUFSIZ];

	inf.open(fname,ios_base::in);
	t1 = upCycle();
	ouf.write(s,sizeof(s));
	t2 = upCycle();
	cout << "write\t\t" << t2-t1 << endl;
	ouf.close();

	t1 = upCycle();
	inf.open(fname,ios_base::in);
	t2 = upCycle();
	inf.close();
	cout << "open\t\t" << t2-t1 << endl;

	inf.open(fname,ios_base::in);
	t1 = upCycle();
	inf.read(buf,ios_base::in);
	t2 = upCycle();
	inf.close();
	cout << "read\t\t" << t2-t1 << endl;

	inf.open(fname,ios_base::in);
	t1 = upCycle();
	inf.close();
	t2 = upCycle();
	cout << "close\t\t" << t2-t1 << endl;



	const char s2[sm_buf] = "This is a random text file used as\nan example\n\nof a file\nfor \n\nprograms to\n\n\n";
	t1 = upCycle();
	ouf.write(s,sizeof(s));
	t2 = upCycle();
	cout << endl << "write\t\t" << t2-t1 << "\tsmaller buffer of " << sm_buf << endl << endl;
	ouf.close();
	return 0;
}
