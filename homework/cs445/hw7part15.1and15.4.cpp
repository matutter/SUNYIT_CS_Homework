// compiler args 
// g++ this.cpp -std=c++0x

// this code opens a program creates a pipe to it an reads it
// the book says something about waitpid, but that's not in figure 15.6

// 15.1 guess: not closing something that a parent and or child is going to
// block on, would cause 1 of two things probably,
// 1. the child that has the resource open never dies... becomes a zombie
// 2. the parent gets blocked on the resource waiting for it to be open-able

// 15.4 guess: well if you remove a signal handler from something and
// send it a signal, there's a good chance it winds up killing it. 
// so in general we can assume that if sigpipe was sent to anything and
// the program wasn't handling it, then sigpipe will kill the program.


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

int main(int argc, char const *argv[])
{
    FILE *in;

    char bfr[512];

    if(!(in = popen("/home/mat/Desktop/hw17_comp.out 1", "r")))
    {
		return 1;
    }

    while(fgets(bfr, sizeof(bfr), in)!=NULL)
    {
        cout << bfr;
    }

    pclose(in);
	return 0;
}