// Copy a file
#include <fstream>      // std::ifstream, std::ofstream
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define PRSET1__  t1 = CPUCycleCounter();
#define PRSET2__  t2 = CPUCycleCounter();

using namespace std;

static inline unsigned long long CPUCycleCounter(void) {
  unsigned long long int x;
  __asm__ volatile (".byte 0x0F, 0x31" : "=A" (x));
  return x;
}

int main () {
  int i;
  ifstream inf;
  ofstream ouf;
  filebuf * buff_stream;
  unsigned long long int t1, t2; //start time end time 
  string text[2] = {"large","small"};
  char* buffer;
  long size;
  char * buf;
  FILE * fp;

cout << endl << "Operation\tCylces" << endl;
for(i=1;i<3;i++)
{
  cout << "*Using a " << text[i-1] << " buffer" << endl;

  buff_stream = inf.rdbuf(); //gets the stream buffer
  PRSET1__
  buff_stream->open("textfile",std::ios::in); //opens textfile as input
  PRSET2__
  cout << "open\t\t" << t2-t1 << endl;

  inf.seekg (0,inf.end);
  size = inf.tellg();
  inf.seekg (0);
  buffer = new char[size/i]; //gets the size and allocates an exact (or 1/2) buffer

  PRSET1__
  inf.read (buffer,size); // reads the file into the buffer
  PRSET2__
  cout << "read\t\t" << t2-t1 << endl;
  PRSET1__
  buff_stream->close(); // close the file for input
  PRSET2__
  cout << "close\t\t" << t2-t1 << endl;
  buff_stream = ouf.rdbuf(); // get an outfile stream
  buff_stream->open("textfile2",std::ios::out); //open it for output

  PRSET1__
  ouf.write (buffer,size); //write it out with an exact (or 1/2) buffer
  PRSET2__
  cout << "write\t\t" << t2-t1 << endl;
  buff_stream->close();
  cout << endl;

}

  cout << "*Using a " << text[i-3] << " buffer" << endl;
  // C style file operations
  buf = (char*) malloc(size);
  PRSET1__
  fp = fopen("textfile","r");
  PRSET2__
  cout << "fopen\t\t" << t2-t1 << endl;
  PRSET1__
  fread(buf, sizeof(char), size, fp);
  PRSET2__
  cout << "fread\t\t" << t2-t1 << endl;
  PRSET1__
  fclose(fp);
  PRSET2__
  cout << "fclose\t\t" << t2-t1 << endl;
  fp = fopen("textfile2","w");
  PRSET1__
  fwrite(buf, sizeof(char), size, fp);
  PRSET2__
  cout << "fwrite\t\t" << t2-t1 << endl;
  fclose(fp);
  free(buf);

  cout << endl;

  //delete[] buffer;
  return 0;
}