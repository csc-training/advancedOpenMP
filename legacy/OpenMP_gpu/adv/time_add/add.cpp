#include <iostream>
#include <cmath>
#include "timer.hpp"
using namespace std;

void add(int n, float *x, float *y)
 { 
// TODO 2b
//F1 #pragma omp target teams distribute parallel for num_teams(108) num_threads(256) //1 .4s
//F2 #pragma omp        teams distribute parallel for num_teams(108) num_threads(256) //2 mins
//F3 #pragma omp              distribute parallel for                num_threads(256) //2 .1s
//F4 #pragma omp              distribute parallel for //             num_threads(256) //2 .1s
   for (int i = 0; i < n; i++) y[i] = x[i] + y[i]; 
 }

int main(void)
{
  Timer_Collector timer;
//int N = 1<<28; //  use 2**28 for timings 
  int N = 1<<25; //  use 2**25 for validating code
  float x[N], y[N], y_value, maxError = 0.0f;

  for (int i = 0; i < N; i++) { x[i] = 1.0f; y[i] = 2.0f; } //init x & Y on host
  y_value=x[0]+y[0];

timer.start(" Alloc and Data TO  ");        // TODO 1 :

  #pragma omp target data map(tofrom:y) map(to:x)
  {
timer.stop();                               // TODO 1 :

timer.start(" Add on GPU         ");        // TODO 1 :

  // TODO 
  //#pragma omp target teams distribute parallel for num_teams(108) num_threads(256)
  //for (int i = 0; i < N; i++) y[i] = x[i] + y[i];

  // TODO 2b
  //F1                                         //1 .4s
  //F2 #pragma omp target                      //3  mins
  //F3 #pragma omp target teams num_teams(108) //2 .1s
  //F4 #pragma omp target teams thread_limit(256) // num_teams(108) //2 .008s
  add(N,x,y);
 
timer.stop();                               // TODO 1 :



timer.start(" Data FROM & Dealloc");        // TODO 1 :
  }
timer.stop();                               // TODO 1 :

  // Check for errors (all values should be 3.0f)
  for (int i = 0; i < N; i++){
    maxError = fmax(maxError, fabs(y[i]-2.0f));
    if(maxError > 0.0000001) {cout << maxError<< " error exceeds e10-6 at i=" << i << endl;}
  }
  std::cout << " Max error:  " << maxError << std::endl;
  std::cout << " for count = " << N        << std::endl;

  timer.print();                            // TODO 1 :

  return 0;
}
