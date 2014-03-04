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
	unsigned int setter_index;
	class child {
	public:
		unsigned int No;
		bool	status;
		pid_t	pid;
		int 	childPid;
		int 	pipe_ends[2];
		string	cmdFile;

		child(unsigned int n, bool s) {
			No = n; status = s;
			if(pipe(pipe_ends)) {
				cout<<"pipe for child " << pid << " failed" << endl;
			}
			pid = fork();
			childPid = getpid();
		}
	};

	void childSync(unsigned int childNo) {
		//cout << "attempting to sync " << childNo << endl;
		if(isParent()) return;
		children[childNo].cmdFile = readPipe(children[childNo].pipe_ends);
		/* other things to sync go here */

		//cout << "sync complete" << endl;

	}
	void childLoop() {
		if(isParent()) return;
		unsigned int childNo = whichChild(getpid());
		//cout << children[childNo].childPid << "["<< childNo << "] test: " ;
        kill(children[childNo].childPid,SIGTSTP); //wait for sync from parent
       	childSync(childNo);
        kill(children[childNo].childPid,SIGTSTP); //begin child main loop

        while(1)
        {
        	cout << children[childNo].childPid << " wants to read " << children[childNo].cmdFile << endl;
        	sleep(1);
        }
        //kill(children[childNo].childPid,SIGTERM);
	}
	string readPipe(int *pipes)
	{
		int i;
		close(pipes[1]);
		char buf[1024];
		string buffer = "cmd.file";
		read(pipes[0], &buf, 1024);
		for(i=0;i<1024;i++) if(buf[i]==0) { buf[i-1] = 0; break; }
		return buf;
	}
	void writePipe(int *pipes, string mes)
	{
		close(pipes[0]);
		FILE *stream;
		stream = fdopen (pipes[1], "w");
		fprintf (stream, "%s\n",mes.c_str());
		fclose (stream);
	}
public:
	pid_t pid, parent;		
	vector<child> children;
	childManager(int number_of_children, pid_t parent) {
		int i=0;

		while(number_of_children--) {
			if(parent == getpid())
			{	
				this->parent = parent;
				children.push_back(child(i++,_IDLE));
				if(!isParent()) childLoop(); 
			}
		}
	}
	template<class TYPE> childManager &set(TYPE var) {
	for(std::vector<child>::size_type i = 0; i != children.size(); i++)
		switch(setter_index)
		{
			case _No	 : break;
			case _STATUS : break;
			case _PID	 : break;
			case _PIPE	 : break;
			case _cmdFile: children[i].cmdFile = var; break;
		}
	return *this;
	}
	void sync() {
		if(!isParent()) return;
		for(child ea : children)
		{
			close(ea.pipe_ends[0]);
			writePipe(ea.pipe_ends,ea.cmdFile);
			wakeUpCall(ea.No);
		}
	}
	void report() {
		string s = "";
		for(child ea : children) 
		  cout << "Child[" << ea.No << "] PID: " << ea.pid << " STATUS: " << (ea.status?"BUSY":"IDLE") << 
				  " PIPES ["<<ea.pipe_ends[0]<<"]["<<ea.pipe_ends[1]<<"]" << 
				  " cmdFile " << ea.cmdFile << endl;
	}
	unsigned int whichChild(pid_t pid) {
		int i = 0;
		for(child ea : children) {
			if(ea.childPid == pid) return i;
			i++;
		}
		return 9999;
	}
	void endChildren() {
		for(child ea : children)	
			kill(ea.pid,9);
	}
	bool good() {
		pid_t res;
		int status;
		for(child ea : children)
			if( waitpid(ea.pid, &status, WNOHANG) )
				return 0;
		return 1;
	}
	childManager &cmdFile() { this->setter_index = _cmdFile; return *this; } // set the setter return the class instance
	bool isParent(void) { return (parent == getpid())?1:0; } // 1 if parent else 0
	void wakeUpAllCall() { for(child ea : children) kill(ea.pid,SIGCONT); } //send SIGCONT to 'ea'ch child
	void wakeUpCall(unsigned int i) { kill(children[i].pid,SIGCONT); }
};