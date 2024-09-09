#include <iostream>
#include <omp.h>
using namespace std;
#define Nthreads 4

#include <vector>
int main() {

  vector<int> array(Nthreads,9);

  int *array_ptr =array.data();
  #pragma omp parallel firstprivate(array_ptr) num_threads(4)
  { 
    // int t = omp_get_thread_num(); 
    // array[t] = t; 
        int t = omp_get_thread_num();
        array_ptr += t;
        array_ptr[0] = t;
  }
  for (auto i: array) cout << i;  cout<<endl;

  #pragma omp parallel num_threads(4)
  { int t = omp_get_thread_num(); 
    array[t] = t; 
  }
  for (auto i: array) cout << i;  cout<<endl;

}
