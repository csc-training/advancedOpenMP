#include <iostream>
#include <omp.h>
#include <sstream>
using namespace std;

void work(int i){
#ifndef _OPENMP
   cout << i << endl;
#else
   // TODO 3: create a single string for printing
   stringstream one_string;
   one_string << i << " from thread " << omp_get_thread_num()<<'\n';
   cout << one_string.str();
#endif
}

class C {
public:
  void class_func() {
     // TODO 1:  Make this worksharing
     #pragma omp for 
    for(int i=0; i<8; i++) { 
      work(i);
    }
  }
};

int main() {
  C c;
  // TODO 1: Create a team of 4 members
  #pragma omp parallel num_threads(4)
  c.class_func();
}
