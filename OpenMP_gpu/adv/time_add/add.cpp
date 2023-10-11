#include <iostream>
#include <cmath>
#include "timer.hpp"
using namespace std;

void add(int n, float *x, float *y)
 { 
//1 #pragma omp target teams distribute parallel for num_teams(108) num_threads(256) //1 .4s
//2 #pragma omp        teams distribute parallel for num_teams(108) num_threads(256) //2 mins
//3 #pragma omp              distribute parallel for                num_threads(256) //2 .1s
    #pragma omp              distribute parallel for //             num_threads(256) //2 .1s
   for (int i = 0; i < n; i++) y[i] = x[i] + y[i]; 
 }

int main(void)
{
  Timer timer;
  int N = 1<<28; // 1M elements
//int N = 1<<25; // 1M elements
  float x[N], y[N]; 

  timer.start("HOST init    ");
  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++) { x[i] = 1.0f; y[i] = 2.0f; }
 #pragma omp target data map(tofrom:y) map(to:x)
{
  timer.stop();
 

//   for (int i = 0; i < N; i++) y[i] = x[i] + y[i];


  timer.start(" GPU  add    ");
//#pragma omp target teams distribute parallel for num_teams(108) num_threads(256)
//for (int i = 0; i < N; i++) y[i] = x[i] + y[i];

//1                                         //1 .4s
//2 #pragma omp target                      //3  mins
//3 #pragma omp target teams num_teams(108) //2 .1s
//4 #pragma omp target teams thread_limit(256) // num_teams(108) //2 .008s
    #pragma omp target teams thread_limit(512) // num_teams(108) //2 
  add(N,x,y);
 
  timer.stop();



  timer.start("HOST check   ");
}
  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for (int i = 0; i < N; i++){
    maxError = fmax(maxError, fabs(y[i]-3.0f));
    if(maxError > 0.0000001) {cout << i << maxError << " at i=" <<  i <<  endl; }
  }
  std::cout << "Max error: " << maxError << std::endl;
  std::cout << " for count = " << N << std::endl;
  timer.stop();
  timer.print();

  return 0;
}
