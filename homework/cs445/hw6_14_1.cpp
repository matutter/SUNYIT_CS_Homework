// compiler args 
// g++ hw6_14_1.cpp -std=c++0x -pthread

// this program will attempt to open a file and set it's write lock
// it will then fork a new process to try and use it while its locked
// the process will only be able to when the thread is finished 
// fctrl() documentation:
// http://pubs.opengroup.org/onlinepubs/7908799/xsh/fcntl.h.html

#include <iostream>      // cout/cin
#include <fstream>       // file stream stuff
#include <fcntl.h>		 // file control
#include <unistd.h>      // system things
#include <sys/types.h>	 // type defines
#include <sys/stat.h>	 // stat syscall
#include <stdio.h>		 // c style standard io
#include <cstring>		 // c style strings
#include <iomanip>		 // hex dump among other tools
#include <sstream>		 // string streams because im lazy

using namespace std;

void action(const char * file_name, short int lock_type, int linger_time);

int main (int argc, char* argv[])
{
	// read  F_RDLCK
	// write F_WRLCK
	const char * fname = "test.file";

	if( fork() == 0 )
		action(fname, F_WRLCK,6);

	sleep(1);
	action(fname, F_WRLCK,0);

	return 0;
}


void action(const char * fname, short int lock_t, int linger_time)
{
	struct flock fd_data;
	int pid = getpid();

	cout << pid << " opening " << fname << endl;

	// get the file descriptor
	int fd = open( fname, O_WRONLY );

	cout << pid << " trying to lock " << fname << endl;

	// clear it
	memset( &fd_data, 0, sizeof(fd_data) );
	fd_data.l_type = lock_t;
	fcntl(fd, F_SETLKW, &fd_data);

	// wait for a continue
	cout << pid << " lock set " << endl;
	cout << pid << " waiting ";

	// block other processes
	for(int i=0; i<linger_time; linger_time--)
	{
		sleep(1);		
		cout << linger_time << " " << flush; 
	}
	cout << endl;

	// when continued unlock
	fd_data.l_type = F_UNLCK;
	fcntl (fd, F_SETLKW, &fd_data);

	cout << pid << " unlocked" << endl;
	close (fd);
	exit(0);
}