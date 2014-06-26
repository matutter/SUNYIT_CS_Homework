//hw1 
// can be used with big.txt, file.txt, and textfile
#include <stdio.h>
#include <stdlib.h> // <-- adds exit for part 2
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
char fname[255]; 
struct stat st;
void noRace();
static void handler(int signo);

int main(int argc, char const *argv[])
{
	int i=0, n=0, k=0, status;
	FILE *fp;
	pid_t pid=1;

	while(1) {

		signal(SIGUSR1, handler); //PART 1
		signal(SIGUSR2, handler); //PART 1
		signal(SIGALRM, handler);

		if(pid == 0)
		{
			fp = fopen(fname, "r");
			if(fp != NULL){
				stat(fname, &st);
				fclose(fp);
				n = st.st_size;
				pid = getpid();
        		
				if(n>255) { kill(pid, SIGALRM); exit(0); }
				else if(n%2) kill(pid, SIGUSR1); //PART 1
					else kill(pid, SIGUSR2);  //PART 1
				exit(n);
			}
			exit(0xFFFF);
			kill(getpid(), 9); //send kill if I become a zombie or cannot find file
		}
		else
		{	
			printf("Enter filenames until you're happy. 'die' to end.\n");
			scanf("%s", fname);
			if(!strcmp(fname,"die")) break;
			pid = fork();	

			wait(&status);
			n = WEXITSTATUS(status);
			if ( n != 0 && pid != 0) //no file too big && no parent
				if(n==0xFFFF) // probably wont be 65535
					printf("\tChild cannot find [%s].\n", fname);
    		    else
	    		    printf("\t%s is %d\n", fname, n);
		}
	}
	printf("Bye bye\n\n");
	return 0;
}

static void handler(int signo) {
	if(signo == SIGALRM)
		printf("\tFile is too big!!!\n");
	else
		printf("\t%s is %s\n",fname, (signo==10)?"odd":"even");
	return;
}

void noRace() { // could be used to avoid race condition in part 1 
  sleep(1);
}
/*
Part 1

Write a program at reads the names of files by reading the standard input. Each time it reads a filename, it creates a new process (using fork) that determines the file's length, using the "stat" system call. If the file length is odd, the child process uses the "kill" system call to send the SIGUSR1 signal to the parent. It the file length is even, the child process sends the SIGUSR2 signal to the parent. When the parent receives the signal, it prints the name of the file and whether its length was odd or even. After printing, the process reads the next line of input from standard input and continues.

PART 2

Use the status of the child (passed back to the parent using the exit library function, see "man 3 exit", and received by the parent using "wait") to report the length of the file back to the parent. Also, print whether odd or even as reported thtough the signal handler above. In addition, if the file length exceeds 255 bytes, use the SIGALRM signal to notify the parent process, so that it can print an error message, instead of odd/even. When the file size exceeds 255 bytes, an length of 0 can be returned, instead of the file length.
*/