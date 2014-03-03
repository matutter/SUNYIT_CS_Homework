// general filesystem event class, 
// let me know if you use or adapt it matutter4@gmail.com
#include	<cstring>
#define		_missingFile	6
using namespace std;
class fileListener
{
	private:
		struct stat st;
		class file_
		{
			public:
			string name;
			unsigned long long modify;
			unsigned int mode;
		};
	public:
	file_ file;

	int addListener(string s) {
		if(!s.size()) return 0;
		file.name = s;
		stat( file.name.c_str(), &st );
		file.modify = st.st_mtime;
		file.mode	= st.st_mode;
		return ( file.modify != _missingFile )? 1 : 0;
	}

	int listenModify(void) {
		if(!file.name.size()) return 0;
		while(1)
		{
			stat( file.name.c_str(), &st );
			file.mode	= st.st_mode;
			if( file.modify == _missingFile ) return 0;
			if( file.modify != st.st_mtime )
			{
				file.modify = st.st_mtime;
				return 1;
			}
		}
		return 0;
	}
};