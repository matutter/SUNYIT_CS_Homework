// g++ version 4.6.3 std=c++0x                             //
// compiler args:                                          //
// g++ this.cpp -Wall -fexceptions -std=c++0x -g -lpthread //
/////////////////////////////////////////////////////////////
#include <sys/inotify.h> //filesystem events
#include <iostream>      //cout/cin
#include <fstream>       //file stream stuff
#include <unistd.h>      //system things
#include <cstring>       //gives me .c_str()
#include <vector>        //vectors
#include <thread>        //threads
#include <mutex>         // mutexes

using namespace std;

mutex _cmdLoc;

class tinyListener {
public:
	string name, list_name;
	void addListener(string s) {
		list_name = s;
	}
	bool good() {
		return (list_name == name);
	}
	bool listenModify() {
		long int	event_size = sizeof(struct inotify_event), 
					buf_size =  1024 * ( event_size + 16 ) ;
		struct inotify_event *event;
		int length, i=0;
		char buffer[buf_size];

		int feed = inotify_init();
		if( feed < 0 ) { return 0; /*cant get inode base*/ } // perm error
		int watch = inotify_add_watch(feed, ".", IN_MODIFY);
		length = read( feed, buffer, buf_size );
		if( length < 0 ) { return 0; /*cant read directory*/ } // bad spelling
			i = 0;
			while ( i < length ) {
				event = ( struct inotify_event * ) &buffer[ i ];
				if ( event->len ) {
					if ( event->mask && IN_MODIFY ) {
						name = event->name;
						return 1;
					}
				}
				i += event_size + event->len;
			}
		inotify_rm_watch(feed, watch);
		close(feed);
		return 0;
	}
};

class commandLine {
public:
	unsigned int line, owner;
	string file;
	commandLine(unsigned int l, unsigned int o, string s) {
		line = l;
		owner = o;
		file = s;
	}
};

void execute(commandLine cl);

int main(int argc, char const *argv[])
{
	vector<thread> ex;
	tinyListener tl;
	string s, file;
	unsigned int i=0, threads = 2, owner = threads;

	cout << "Number of threads : ";
	cin >> threads;
	cout << "File to watch : ";
	cin >> file;

	tl.addListener(file);

	while(tl.listenModify()) {
		if(tl.good()) {
			cout << "change detected" << endl;

			ex.clear();
			owner = threads;
			i=0;

			ifstream stream(file.c_str(), std::ofstream::binary);
			while(stream.is_open() && !stream.eof())
			{
				getline (stream,s);
				ex.push_back(thread(execute,commandLine(++i,owner--, file)));
				if(owner < 1) owner = threads;
			}
			stream.close();

			for(i=0;i<ex.size();i++)
				ex[i].join();
		}
	}
return 0;
}

void execute(commandLine cl) {
	_cmdLoc.lock();
	unsigned int i=0;
	string s;
	ifstream stream(cl.file.c_str(), std::ofstream::binary);
	while(stream.is_open() && !stream.eof())
	{
		getline (stream,s);
		if(s.size() > 0 && s != "\n" && ++i == cl.line) 
			break;
	}
	stream.close();
	_cmdLoc.unlock();

	s += " >> hw5_THREAD_" + to_string(cl.owner);
	system(s.c_str());
}