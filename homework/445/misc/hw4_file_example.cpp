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
#include	<stack>
#include	"fileListener.h"

using namespace std;


class commandLine {
public:
	unsigned int line, owner;
	commandLine(unsigned int l, unsigned int o) {
		line = l;
		owner = o;
	}
};


int main(int argc, char const *argv[])
{
	

string cmd;
vector<string> buffer;
vector<commandLine> assign;
string file = "cmd.file";
int i=0, threads = 3, owner = threads;
	fileListener fl;
	fl.addListener("cmd.file");

	while(!fl.empty())
	{
		//if(fl.empty()) break;
		ifstream stream(file.c_str(), std::ofstream::binary);
		while(stream.is_open() && !stream.eof())
		{
			getline (stream,cmd);

			if(cmd.size() > 0 && cmd != "\n") {
				buffer.push_back(cmd);
				assign.push_back(commandLine(i++,owner--));
				if(owner < 1) owner = threads;
			}
		}
		stream.close();


		cout << "line\tthread\tcommand" << endl;
		for(commandLine ea : assign)
			cout << ea.line << "\t" << ea.owner << endl;
		
		if(!buffer.empty() && 0)
		{
			cmd = buffer.back();
			buffer.pop_back();

			ofstream stream2(file.c_str(), std::ifstream::binary);
			stream2.seekp(ios_base::beg);
			stream2 << "";
			stream2.close();

		}
		buffer.clear();
		return 0;
	}
	cout << "cmd file empty" << endl;
return 0;
}
/*

one 1
two 2
three 3
four 4

one 1
two 2
three 3
four 4

*/