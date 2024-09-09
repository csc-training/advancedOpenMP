#include <iostream>
#include <omp.h>
#include <sstream>
using namespace std;

void work(int i){
#ifndef _OPENMP
   cout << i << endl;
#else
   // TODO 3: create a single string for printing
   
#endif
}

class C {
public:
  void class_func() {
     // TODO 1:  Make this worksharing
     // #pragma omp
    for(int i=0; i<8; i++) { 
      work(i);
    }
  }
};

int main() {
  C c;
  // TODO 1: Create a team of 4 members
  // #pragma omp
  c.class_func();
}
