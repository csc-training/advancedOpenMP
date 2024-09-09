#include <stdio.h>
#include <omp.h>

void fun(int i, float *x, float *y);

int main(){

  int    n=1<<7; 
  float* x=(float*)malloc(n*sizeof(n));
  float* y=(float*)malloc(n*sizeof(n));

  for (int i=0; i<n; i++){ x[i]=100.0f; y[i]=200.0f;}

// TODO 1:  Offload with worksharing target...parallel for
//          and map x data in an efficient way--
//          it is only read on the device
  #pragma omp target teams distribute parallel for \
               map(tofrom: y[0:n]) map(to: x[0:n])
  for (int i=0; i<n; i++) fun(i,x,y);

  for (int i=0; i<n; i++) printf(" %d %.0f\n",i,y[i]);

  return 0;
}
