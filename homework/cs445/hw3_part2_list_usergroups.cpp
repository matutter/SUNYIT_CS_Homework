// cat /etc/passwd -> give all users
// groups :user:  -> gives groups they belong to
// simple example using pipe(s)
// compiler (g++ 4.6.3)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define die(e) do { fprintf(stderr, e); exit(EXIT_FAILURE); } while (0);

int main(int argc, char const *argv[])
{
	int link[2], status=0, n, n2, i;
	pid_t pid;
	char buffer[8192];	//one page of mem
	string s, sub;
	vector<char *> arg_vec;
	vector<string> args;

	if (pipe(link)==-1) die("pipe");		// make pipe/close pipe if fail or busy
	if ((pid = fork()) == -1) die("fork");	// make fork/look for bad fork

if(pid == 0)
{
	dup2 (link[1], STDOUT_FILENO);	//duplciate file descritor for child to write to
	close(link[0]);
	execl("/bin/cat", "cat", "/etc/passwd", (char *)0);	
}
else
{	
	close(link[1]);
    read(link[0], buffer, sizeof(buffer));
	s = buffer;

	while(s[0]=='#')				//get rid of dognet crap
		s.erase(0,s.find("\n")+1);

	while(!s.empty())
	{
		n = s.find("\n");			//find the endline buffer
	 	sub = s.substr(0,n);		//get that line in a sub
		s.erase(0,n+1);				//get erase that line in buffer
		args.push_back( sub.substr(0,sub.find(":")) );	//get first part in sub
    }
    
    for(vector<string>::iterator it = args.begin(); it != args.end(); ++it)
		arg_vec.push_back(&(*it)[0]);

	execvp("groups", arg_vec.data());
}
return 0;
}