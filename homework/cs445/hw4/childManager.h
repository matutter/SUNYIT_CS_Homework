// general child manager class, 
// let me know if you use or adapt it matutter4@gmail.com
#include	<iostream>
#include	<fstream>
#include	<sys/wait.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include 	<signal.h>
#include	<cstdlib>
#include	<vector>
#include	<unistd.h>
#include	<string>
#include	"alert.h"

#define		_IDLE	0
#define		_BUSY	1
#define		_SYNC	0
#define 	_No		1
#define		_STATUS 2
#define		_PID 	3
#define		_PIPE 	4
#define		_cmdFile 5

using namespace std;
class childManager
{
private:
	class child {
	public:
		unsigned int No;
		bool	status;
		pid_t	pid, parentPid;
		int 	pipe_ends[2];
		char *	cmdFile;
		void initChild(unsigned int n, bool s, string file, int parent) {
			No = n; status = s;
			if(pipe(pipe_ends)) {
				cout<<"pipe for child " << pid << " failed" << endl;
			}
			cmdFile = new char[file.size() + 1];    	// string to usable c style string
			copy(file.begin(), file.end(), cmdFile);	// now i can open files with it
			cmdFile[file.size()] = '\0';				//
			
			parentPid = parent;							// parent pid inside child & parent		
			pid = fork();								// child pid inside parent
			if(getpid() == parent) return;				// only child operations
			pid = getpid();								// child pid in child
		}
	};
	//child's main loop
	void childLoop() {
		if(isParent()) return;
        stopChild(ea.pid);

        while(1)
        {    	
        	//cout << "in the child " << ea.pid << endl;
        	string cmd;
        	vector<string> buffer;
        	ifstream stream(ea.cmdFile, std::ofstream::binary);
			while(stream.is_open() && !stream.eof())
			{
				getline (stream,cmd);
				if(cmd.size() > 0 && cmd != "\n")
					buffer.push_back(cmd);
			}
			stream.close();

			//cout << "#com[" << buffer.size() << "]\t";
			
			if(!buffer.empty())
			{
				cmd = buffer.back();
				buffer.pop_back();


				ofstream stream2(ea.cmdFile, std::ifstream::binary);
				stream2.seekp(ios_base::beg);
				for(string each : buffer) 
					stream2 << each << endl;
				
				//cout << "pos[" << stream2.tellp() << "]\t";	
				//cout << "cmd["<< cmd << "]" << endl;
				stream2.close();

			}
			buffer.clear();
			fork();
			if(getpid() != ea.pid) { 
				//cout << getpid() << endl;
				char str[12]; // 12 can fit a long int
				sprintf(str,"%ld",(long)ea.pid);
				cmd += " > " + string(str) + ".hw4_result";			
				system(cmd.c_str());
				kill(getpid(),9);
			}
        	stopChild(ea.pid);
        }
	}
public:
	pid_t pid, parent;
	child ea;
	// create a new managed child and put it in its main loop
	childManager(pid_t parent, string file) {
		if(parent == getpid())
		{	
			this->parent = parent;
			this->ea.initChild(0, _IDLE, file, parent);
			if(!isParent()) childLoop();
		}
	}
	// kill all children
	void endChild(pid_t pid) {	
		kill(pid,9);
	}
	// 1 if parent else 0
	bool isParent(void) {
		return (parent == getpid())?1:0;
	}
	//send stop signal to child
	void stopChild(pid_t pid) {
		//alert("stop child ", pid, " ");
		if(isParent()) return;
		kill(pid,SIGTSTP);
	}
	//returns 1 if child is alive
	bool good(void) {
		int status;
		//cout << "waiting for stop" << endl;
		waitpid(ea.pid, &status, WSTOPPED);
		WIFSTOPPED(status);
		//cout << "child stopped" << endl;
		return 0;
	}
	//makes the child do 1 main loop
	void wakeup(void) {
		
		kill(ea.pid,SIGCONT);
		good();
	}
	void report() {
		string s = "";
		  cout << "Child[" << ea.No << "] PID: " << ea.pid << " STATUS: " << (ea.status?"BUSY":"IDLE") << 
				  " PIPES ["<<ea.pipe_ends[0]<<"]["<<ea.pipe_ends[1]<<"]" << 
				  " cmdFile " << ea.cmdFile << endl;
	}
};