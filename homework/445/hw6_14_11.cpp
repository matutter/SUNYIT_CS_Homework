// compiler args 
// g++ hw6_14_1.cpp -std=c++0x -pthread

// this program will open a file and creat a mmap() into it
// then the file descriptor will be closed.
// the purpose is to demonstrate the memory mapped reagon will 
// still be accessable.

#include <iostream>		 // cout/cin
#include <fstream>		 // file stream stuff
#include <fcntl.h>		 // file control
#include <unistd.h>		 // system things
#include <sys/types.h>	 // type defines
#include <sys/stat.h>	 // stat syscall
#include <stdio.h>		 // c style standard io
#include <cstring>		 // c style strings
#include <iomanip>		 // hex dump among other tools
#include <sstream>		 // string streams because im lazy
#include <sys/mman.h>	 // memory manager for mmap()
#include <cstdlib>		 // exit

using namespace std;

void fd_fail();
void fmap_fail();
const char * c_str(string s);

int main(int argc, char const *argv[])
{

	char fname[10] = "test.file";
	int res, bytes = 100, fsize = bytes*sizeof(char);
	char * fmap;

	// create descriptor
	int fd = open( fname,  O_RDWR | O_CREAT );
	if(fd < 0)
		fd_fail();

	// expand the file's size to 'bytes' characters
	res = lseek(fd, fsize-1, SEEK_SET);
	if(res < 0)
		fd_fail();

	// write 0000'0000 to last byte
	// forces the size to remain atleast as large as we want
	res = write(fd,"",1); 
	if(res < 0)
		fd_fail();

	// # . arg
	// 1 . start address
	// 2 . length
	// 3 . protection(s)
	// 4 . flags
	// 5 . fd
	// 6 . offset  
	fmap = (char *)mmap(0, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(fmap == MAP_FAILED)
		fmap_fail();


	cout << "File opened and mapped." << endl
		 << "Writing to map" << endl;
	int byte = 0;
	for(; byte<bytes/2; byte++)
	{
		fmap[byte] = 'B';
	}

	close(fd);
	cout << "File descriptor closed." << endl;
	fmap[byte++] = '\n';

	for(; byte<bytes-1; byte++)
	{
		fmap[byte] = 'A';
	}
	fmap[byte++] = '\n';
	cout << "Write finished." << endl;

	cout << "B = before | A = after | there are 2 \\n | 100 characters total" << endl;

	// unmap
	munmap(fmap,fsize);



	return 0;
}

void fmap_fail()
{
	string msg = "failed to establish memory map in file... ";
	stringstream s;
	s << getpid();
	msg += s.str();
	perror( c_str(msg) );
	exit(1);	
}

void fd_fail()
{
	string msg = "failed to establish fd on file... ";
	stringstream s;
	s << getpid();
	msg += s.str();
	perror( c_str(msg) );
	exit(1);
}

const char * c_str(string s)
{
	return (char*)s.c_str();
}