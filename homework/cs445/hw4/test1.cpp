/* Using 'wait();' and an '__EXIT_STATUS' makes sure we don't have zombies or a race condition */ 
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<sys/stat.h>
#include 	<iostream>
#include	<cstring>
#include	"fileListener.h"
#include	"childManager.h"

using namespace std;

int  main(void)
{
	int		n = 0;
	pid_t	pid = 1;
	string	cmdFile;

	fileListener fl;
	cout << endl << "number of children : ";
	cin >> n;
	childManager cm(n,getpid());

	if(cm.isParent()) { 

		cout << "Enter name of command file: ";
		cin  >> cmdFile;
		cm.cmdFile().set(cmdFile).sync();
		//cm.report();

		cout << (fl.addListener(cmdFile)?"Listener added for ":"Failed to add listener for ") << fl.file.name << endl;
		sleep(1); //avoiding the need for synchronisity
		while(fl.listenModify())
		{
			//cout << "file change detected " << endl;
			if(cm.good()); //check if children exist
			cm.wakeUpAllCall();
			if(!cm.good()) { cout << endl << "children are abnormal" << endl; break; } 
		}
		cm.endChildren();

	}
	cm.report();

	return 0;
}

