//hw1 
#include <stdio.h>
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

		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);

		if(pid == 0)
		{
			fp = fopen(fname, "r");
			if(fp == NULL){
				printf("Child cannot find [%s].", fname);
				fclose(fp);
			}
			else {
				stat(fname, &st);
				fclose(fp);
				n = st.st_size;
				pid = getpid();
				if(n%2) kill(pid, SIGUSR1);
					else kill(pid, SIGUSR2);
			}

				kill(getpid(), 9); //send kill
				wait(&status);	//double tap
		}
		else
		{
			noRace();		

			printf("Enter filenames until you're happy. 'die' to end.\n");
			scanf("%s", fname);
			if(!strcmp(fname,"die")) return 0;
			pid = fork();
		}

	}
	printf("Bye bye\n\n");
	return 0;
}

static void handler(int signo) {
	if(signo-10) printf("%s is even.\n", fname); else printf("%s is odd.\n", fname);
}

void noRace() {
	int i;
	for( i=0;i<3;i++ )
		for( i=0;i<100000000;i++ );
}
