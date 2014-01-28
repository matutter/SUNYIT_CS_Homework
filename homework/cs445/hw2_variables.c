//hm1 
#include <stdio.h>
#include <sys/types.h>
#include <wchar.h>
int fwide(FILE *fp, int mode);
int fflush(FILE *fp);


int main(int argc, char const *argv[])
{
	
	printf(	"Write a program at reads the names of files by reading the standard input.\n"
			"Each time it reads a filename, it creates a new process (using fork) that \n"
			"determines the file's length, using the \"stat\" system call. \n"
			"If the file length is odd, the child process uses the \"kill\" system call \n"
			"to send the SIGUSR1 signal to the parent. If the file length is even, \n"
			"the child process sends the SIGUSR2 signal to the parent. When the parent \n"
			"receives the signal, it prints the name of the file and whether its length\n"
			" was odd or even. After printing, the process reads the next line of input \n"
			"from standard input and continues.\n\n\n");

	int pid = fork();

	if (pid < 0) { // error occurred 
		fprintf(stderr, "Fork failed!\n");
		//exit(-1);
	}else if (pid == 0) { // child process 
		printf("I am the child, return from fork=%d\n", pid);
		//execlp("/bin/ps", "ps", NULL);
	}else { // parent process 
		printf("I am the parent, return from fork, child pid=%d\n", pid);
		printf("Parent exiting!\n");
		//exit(0);
	}

	return 0;
}