// compiler args           //
// g++ this.cpp -std=c++0x //
/////////////////////////////
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

	cout << "You will be asked for a file to listen to." << endl << "Then you may type shell commands in that file and save it to run them" << endl;


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
		while(!fl.empty())
			for(childManager ea : cm) {
				if(!fl.empty()) {
					ea.wakeup();
				}
			}
		sleep(1);	
		cout << cmdFile << " is empty" << endl;
	}
	return 0;
}

