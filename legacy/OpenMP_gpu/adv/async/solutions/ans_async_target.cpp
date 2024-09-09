#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void host_independent_parallel_work(){ sleep(1); }

int main(){
int n=1<<4; // 16

  int p[n],v1[n],v2[n]; 

// TODO 2a: create a prallel region with three threads.
  #pragma omp parallel num_threads(3)
  {
// TODO 2b: use master|masked to have a single generator thread
    #pragma omp master //masked
    {
//TODO 1a: add nowait and depend(out:...) and appropriate map
      #pragma omp target nowait  depend(out:v1) map(from:v1)
      for(int i=0;i<n;i++) v1[i]=2;
  
//TODO 1b: add nowait and depend(out:...) and appropriate map
      #pragma omp target nowait depend(out:v2) map(from:v2)
      for(int i=0;i<n;i++) v2[i]=1;  

//TODO 1c: add nowait and depend(in:...) and appropriate maps
//         for v1,v2 and p.  (optional: depend(out:p))*
      #pragma omp target nowait depend(in:v1,v2) depend(out:p) \
                                   map(to:v1,v2)   map(from:p)
      for(int i=0;i<n;i++) p[i]=v1[i]*v2[i];
    }
    host_independent_parallel_work();

//TODO 1d: wait for target asks to complete here.
    #pragma omp taskwait
                         // or #pragma task depend(in:p)*

// TODO 2c: use master|masked for a single thread here.
    #pragma omp master //masked
    for(int i=0; i<n;   i++) assert(p[i]==2); //Validate
  }

  printf("Passed OpenMP %d\n", _OPENMP);
}
