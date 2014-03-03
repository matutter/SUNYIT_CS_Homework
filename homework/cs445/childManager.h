#include	<sys/types.h>
#include 	<signal.h>
#include	<cstdlib>
#include	<vector>
#define		_IDLE	0
#define		_BUSY	1
using namespace std;
class childManager
{
private:
	class child {
	public:
		unsigned int No;
		bool	status;
		pid_t	pid;
		int 	pipe_ends[2]; //these are the ends of pipes

		child(unsigned int n, bool s) {
			No = n; status = s;
			if(pipe(pipe_ends)) {
				cout<<"pipe for child " << pid << " failed" << endl;
			}
			pid = fork();
		}
	};

public:
	pid_t pid, parent;		
	vector<child> children;
	childManager(int number_of_children, pid_t parent) {
		int i=0;

		while(number_of_children--) {
			if(parent == getpid())
			{	
				this->parent = parent;
				children.push_back(child(++i,_IDLE));
				
				if(parent != getpid()) childLoop();//cout << children.size();
			}
		}
	}
	bool isParent(void) {
		return (parent == getpid())?1:0;
	}
	void wakeUpCall() {
		//sigstop
		//sigcont
		cout << "sending wakeup call" << endl;
		for(child ea : children) 
			kill(ea.pid,SIGCONT);
	}
	void childLoop() {
		// child side
        char *buff = NULL;
        char byte = 0;
        int count = 0;

        buff_stream = inf.rdbuf();

        //cout << getpid() << " going to sleep" << endl;
        kill(getpid(),SIGTSTP);
        //cout << getpid() << " awake" << endl;

        while(1)
        {
        	//sleep(2); cout << getpid()<< " heartbeat" << endl;
        	ifstream infile("test.txt");

			if (infile.good())
			{
				string sLine;
				getline(infile, sLine);
				cout << sLine << endl;
			}

			  infile.close();



        }
        
/*
        // close write side. don't need it.
        close(fd[1]);
        while (read(fd[0], &byte, 1) == 1)
        {
            if (ioctl(fd[0], FIONREAD, &count) != -1)
            {
                fprintf(stdout,"Child: count = %d\n",count);

                // allocate space for the byte we just read + the rest
                //  of whatever is on the pipe.
                buff = malloc(count+1);
                buff[0] = byte;
                if (read(fd[0], buff+1, count) == count)
                    fprintf(stdout,"Child: received \"%s\"\n", buff);
                free(buff);
            }
            else
            {   // could not read in-size
                perror("Failed to read input size.");
            }
        }*/
	}
	void report() {
		string s = "";
		for(child ea : children) 
		  cout << "Child[" << ea.No << "] PID: " << ea.pid << " STATUS: " << (ea.status?"BUSY":"IDLE") << 
				  " PIPES ["<<ea.pipe_ends[0]<<"]["<<ea.pipe_ends[1]<<"]" << endl;
	}

};