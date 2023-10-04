#include <assert.h>
#include <stdio.h>

int main(){
  int a=2, n=1<<4; // 16
  int x[n], y[n];


  // TODO 1c:  create a data region around this block
  //           with minimum data motion

  {
     // TODO 1a: offload without any mapping

     for(int i=0; i<n; i++) 
     { 
       x[i] = 1; y[i] = 1;
     }

     // TODO 1b: offload without any mapping

     for(int i=0; i<n; i++) 
     { 
       y[i]=a*x[i]+y[i];
     }
  }

  for(int i=0; i<n; i++) assert(y[i]==3);//Validate

    printf("Passed OpenMP %d\n", _OPENMP);
}
