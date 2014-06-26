#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
using namespace std;
static void handler(int signo) {
	int 	status;
	switch(signo)
	{
		case SIGUSR1:	cout << "Odd file" << endl; break;
		case SIGUSR2:	cout << "Even file"<< endl; break;
		case SIGALRM:	cout << "File is too big or does not exist"<< endl; return;
	}
	wait(&status);
	cout << "Size = " << WEXITSTATUS(status) << endl;
}
int main(int argc, char const *argv[])
{
	struct 	stat st;
	pid_t 	pid;
	string 	s;
	int child;

	while(1)
	{
		if(pid != 0) { // parent

			
			signal(SIGUSR1,handler);
			signal(SIGUSR2,handler) << endl;
			signal(SIGALRM,handler) << endl;


			cout<<"Enter a filename: ";
			cin >> s;

			pid = fork();
		}
		else
		{
			child = getpid();
			if(	stat(s.c_str(),&st) || st.st_size > 255) {
				kill(child,SIGALRM);
			}
			else switch(st.st_size%2)
			{
				case 1: kill(child,SIGUSR1);break;
				case 0: kill(child,SIGUSR2);	break;
			}
			exit(st.st_size);
		}
	}
	return 0;
}