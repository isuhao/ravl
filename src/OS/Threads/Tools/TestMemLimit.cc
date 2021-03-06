////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/PThread/Launch.hh"
#include "amma/PThread/Thread.hh"
#include <iostream.h>
#include <stdlib.h>
#include <unistd.h>

class TestC {
public:
  void EatMemory(int &no) {
    std::cerr << "MemEater " << no << "started.\n";
    for(int k = 0;k < 100;k++) {
      char *at = (char*)malloc(1000000);
      for(int j = 0;j < 7812;j++)
	at[j * 128] = 1;
    }
    std::cerr << "MemEater " << no << "done.\n";
    PThread::Yield();
  }
};

int main()
{
  using namespace PThread;
  TestC ae;
  for(int i = 0;i < 5;i++) {
    Launch(ae,&TestC::EatMemory,i);
  }
  std::cerr << "Done\n";
  sleep(100);
  return 0;
}

