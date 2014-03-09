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
			unsigned long int size;
			unsigned int mode;
		};

	public:
	file_ file;

	int addListener(string s) {
		if(!s.size()) return 0;
		file.name = s;
		if( stat( file.name.c_str(), &st )!=0 ) return 0;
		update();
		return 1;
	}

	int listenModify(void) {
		unsigned long long lastModify = 0;
		while(1)
		{
			lastModify = file.modify;
			if(!update()) return 0;					//if cannot find file end
			if(lastModify != file.modify) return 1; //return 1 if updated
		}
		return 0;
	}
	bool empty(void) {
		update();
		//cout << file.size << "\t" ;
		if(file.size == 0) return 1;
		return 0;
	}
	bool update(void){
		if(stat( file.name.c_str(), &st ) != 0) return 0;
		file.modify = st.st_mtime;
		file.mode	= st.st_mode;
		file.size	= st.st_size;
		return 1;
	}
};