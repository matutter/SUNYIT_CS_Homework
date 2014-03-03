/* Using 'wait();' and an '__EXIT_STATUS' makes sure we don't have zombies or a race condition */ 
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<sys/stat.h>

#include 	<iostream>
#include	<cstring>
#include	"fileListener.h"
#include	"childManager.h"

using namespace std;
void write_to_pipe (int file)
 {
   FILE *stream;
   stream = fdopen (file, "w");
   fprintf (stream, "hello, world!\n");
   fprintf (stream, "goodbye, world!\n");
   fclose (stream);
 }

int  main(void)
{
	int		n = 0;
	pid_t	pid = 1;
	string	cmdFile;

	int 	mypipe[2];

	fileListener fl;
	childManager cm(2,getpid());

	if(cm.isParent()) { cm.report();

		cout << endl << "Enter name of command file: ";
		cin  >> cmdFile;
		cout << (fl.addListener(cmdFile)?"Listener added for ":"Failed to add listener for ") << fl.file.name << endl;
		sleep(1);
		while(fl.listenModify())
		{
			cout << "file change detected " << endl;
			//close(cm.children[0].pipe_ends[0]);
			//write_to_pipe(cm.children[0].pipe_ends[1]);
			cm.wakeUpCall();

		}

	}


	return 0;
}

