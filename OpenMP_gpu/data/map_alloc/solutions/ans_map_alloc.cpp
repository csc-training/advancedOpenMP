#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
int a=2, n=1<<4; // 16

  int x[n], y[n];
  for(int i=0;i<n;i++){ y[i]=1; } // only init y

// TODO 1: only allocate space for x on device
// 1/2 the transfers 
  #pragma omp target map(alloc:x) map(tofrom:y)
  {
     for(int i=0;i<n;i++) x[i]=1;
     for(int i=0;i<n;i++) y[i]=a*x[i]+y[i];
  }

  for(int i=0; i<n; i++) assert(y[i]==3);//Validate

    printf("Passed OpenMP %d\n", _OPENMP);
}

