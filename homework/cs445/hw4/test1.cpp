/* Using 'wait();' and an '__EXIT_STATUS' makes sure we don't have zombies or a race condition */ 
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<sys/stat.h>
#include 	<iostream>
#include	<cstring>
#include	<vector>
#include	"fileListener.h"
#include	"childManager.h"

using namespace std;

int  main(void)
{
	int		n = 2;
	pid_t	pid = 1;
	string	cmdFile;
	vector<childManager> cm;

		cout << "Enter name of command file: ";
		//cin  >> cmdFile;
		cmdFile = "cmd.file";


		fileListener fl;
		cout << (fl.addListener(cmdFile)?"Listener added for ":"Failed to add listener for ") << fl.file.name << endl;
		sleep(1);

		for(;n;n--)
			cm.push_back( childManager(getpid(),cmdFile) );


		while(fl.listenModify())
		{
			cout << "changes detected " << endl;
			while(!fl.empty()) {
				sleep(1);
				for(childManager ea : cm) {
					if(ea.good()) {
						ea.wakeup();
						cout << "waking up" << endl;
					}
				}				
			}
		}
		//cm.endChildren();

	//}
	//cm.report();

	return 0;
}

