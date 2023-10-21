#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;

// TODO 2: include timer.hpp here
#include "timer.hpp"
int main(void)
{
//int     N = 1<<28;
  int     N = 1<<30;
  float x[N], y[N], a=2.0f; 

  // TODO 2: Instantiate timer object here 
  Timer_Collector timer;

  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++) { x[ i] = 1.0f; y[ i] = 1.0f; }

  // TODO 2: Start timer here
  timer.start("    Offload     ");
  // TODO 1: Offload with teams distribute parallel for
  #pragma omp target teams distribute parallel for        //blk
  { for (int i = 0; i < N; i++) y[i] = a*x[i] + y[i]; }

  // TODO 2: Stop timer here and report resuls
  timer.stop();
  timer.print();

  //Insert after axpy calculation
  for (int i=0; i<N; i++)
    assert( (fabs(y[i]-3.0f)) < 0.000001);
  cout << " Passed Validation "<< endl;

  return 0;
}
