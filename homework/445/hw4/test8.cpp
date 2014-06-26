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

int main(int argc, char const *argv[])
{
	

string cmd;
vector<string> buffer;
string file = "cmd.file";

	fileListener fl;
	fl.addListener("cmd.file");

	while(!fl.empty())
	{
		//if(fl.empty()) break;
		ifstream stream(file.c_str(), std::ofstream::binary);
		while(stream.is_open() && !stream.eof())
		{
			getline (stream,cmd);
			if(cmd.size() > 0 && cmd != "\n")
				buffer.push_back(cmd);
		}
		stream.close();

		cout << "#com[" << buffer.size() << "]\t";
		
		if(!buffer.empty())
		{
			cmd = buffer.back();
			buffer.pop_back();


			ofstream stream2(file.c_str(), std::ifstream::binary);
			stream2.seekp(ios_base::beg);
			for(string ea : buffer) 
				stream2 << ea << endl;
			
			cout << "pos[" << stream2.tellp() << "]\t";	
			cout << "cmd["<< cmd << "]" << endl;
			stream2.close();

		}
		buffer.clear();
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