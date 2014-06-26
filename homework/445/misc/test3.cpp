// the compile args                                         //
// g++ this.cpp -Wall -fexceptions -std=c++0x -g -lpthread  //
//////////////////////////////////////////////////////////////
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mx;
int j=0;
static void foo() {
cout << "A" << j++ << endl;
  mx.lock();
  for (unsigned int i = 0; i < 100000000; ++i)
  {
    /* code */
  }
  cout << "B" << j++ << endl;
  cout << "FOO BAR\n";
  mx.unlock();
}

int main() {
  thread t(foo);
  thread t2(foo);
  
  t.join();
  t2.join();

  return 0;
}