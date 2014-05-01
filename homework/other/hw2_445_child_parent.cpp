#include	<iostream>
#include	<fstream>
#include	<sys/wait.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include 	<signal.h>
#include	<cstdlib>
#include	<unistd.h>
#include	<string>
using namespace std;

int 	parent;
bool 	isparent(void);
static 	void handle(int signo);

int main(int argc, char const *argv[])
{
	pid_t 	pid;
	bool 	no_kids = 0;
	struct 	stat st;
	int 	status;
	string 	filename;
	parent 	= getpid();

	while(1)
	{
		if(isparent())
		{
			//cout << "P : " << endl;
			signal(SIGUSR1, handle);
			signal(SIGUSR2, handle);
			signal(SIGALRM, handle);

			if(no_kids)
			{
				wait(&status);
				cout << WEXITSTATUS(status) << " )" << endl;
			}
			else
				no_kids = 1;

			sleep(1);
			cout << "file to check: ";
			cin >> filename;
			pid = fork();
		}
		else
		{
			//cout << "C : " << endl;
			if(	!stat(filename.data(), &st) )
			{ // if its found
				int odd = st.st_size%2;

				if(st.st_size > 255)
				{
					kill(getpid(),SIGALRM);
					exit(0);
				}
				else if(odd)
					kill(getpid(),SIGUSR1);
				else
					kill(getpid(),SIGUSR2);
				exit(st.st_size);
			}
			else
			{ //if file is not found
				cout << "\t can't find file ( err " << flush;
				kill(getpid(),SIGKILL);
			}
			//sleep(1);
		}
	}
	return 0;
}

bool isparent() {
 return (getpid()==parent);
}

static void handle(int signo)
{
	if(signo == SIGUSR1)
	{
		cout << "\tFile is odd ( ";
	}
	else if(signo == SIGUSR2)
	{
		cout << "\tFile is even ( ";
	}
	else if(signo == SIGALRM)
	{
		cout << "\tFile is TOO BIG ( err ";
	}
}