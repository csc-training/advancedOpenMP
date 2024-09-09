##  if clause and clock period counter

## BACKGROUND
The "if" clause argument can be a conditional expression
which can turn on or off the application of the directive 
at runtime.  It is a good way to determine if it is 
reasonable to perform a loop with worksharing or no.

You can use a clock period counter, to get an accurate
estimate of the overhead of a parallel construct.
(Solutions are shown an end.)

# Exercise

1.)  Review the basic reduction code:

     ex2.c

     What would happen if the initial value of sum is not 0.0e0?

2.)
     copy ex2.c to ex2b.c

     In ex2b.c calculate the following cutoff with this statement:

   a n_cuttoff = 20000 + N/omp_get_num_procs();  // or vv
   a n_cuttoff = 20000 + N/omp_get_max_threads();

     (where N is the number of iterations).

   b Use omp_get_num_procs()   as an argument to a num_threads clause.
   b Use omp_get_max_threads() as an argument to a num_threads clause.

   c include an "if clause" to execute the loop N>ncuttoff
  
   d Compile and run:

     cc -fopenmp ex2b.c
     export OMP_NUM_THREADS=64
     ./a.out 

     See code ex2b.c below AFTER you are finished doing the 
     modifications and testing yourself.
     What would happen if the initial value of sum is not 0.0e0 here?


C.)
     The 20000 base is just a rough estimate for a real cutoff base.
     By measuring the cost of the overhead, we can determine a better value.
     Look over the timer.c code.  ts_timer() gets the value in the
     Time Stamp register (number of clock periods (Hz) used).

     The cores run nominally at 1.5GHz (2.1 for SKX, what for LUMI).  
     How many seconds are in a clock period? 

     Copy ex2.c to ex2c.c.
     Use the ex2c.c code to:
            determine a base serial execution cost, and then
            the overhead of a parallel region

            (Later, we will evaluate the cost of forking threads for the first time).

       Code Changes:
```
       #define N 272
       long long tsc_timer(void);
       ...
       long long k0, k1, kt=0;
       ...
       k0 = tsc_timer();
         <parallel loop>
       kt = kt + tsc_timer()-k0;
       printf("Execution cost (clock periods) %ld\n",kt);
```

   1.) Serial execution
```
       cc -c timers.c; 
       cc ex2c.c timers.o
       ./a.out

```
       How many clock periods does it take to run the reduction serially.

   2.) Parallel execution

       Now compile and run it on 64 cores:

       icc -qopenmp ex2c.c timers.o
       export OMP_NUM_THREADS=64
       ./a.out
   
       How many seconds does it take to run the reduction in parallel.  
       (use 1.4GHz for KNL or 2.1GHz for SKX; X-clockperiods/1.4x10^9), etc.)
       Wow!! This is long.  What is the problem.
       (Hint, could this be due to a one-time cost of starting a the OpenMP
        runtime, and loading an *.so files?)

       (Check your results against those below for ex2d.F90 in the next exercise.)

   3.) Now, look at ex2d.c below.
       It measures the initial start up, and does and calculates 
       a true overhead for forking.
```
       icc -qopenmp ex2d.c timers.o
       export OMP_NUM_THREADS=68
       ./a.out
``` 
       What is the true cost of the parallel forking?


   4.) Try this on another platform (e.g.Skylake if you have been using KNL)
       What is the initial fork cost on this system?

   5.) Experiment using fewer cores?
       Does the startup depend upon the number of cores?


## PROGRAN ex2b.c (answer):

```
#include "omp.h"
#include <stdio.h>
#define N 25000
int main(){

   int   i, n_cutoff, n_overhead=20000;
   double sum = 0.0e0;
   
   n_cutoff = n_overhead + N/omp_get_max_threads(); // 21562
   
   #pragma omp parallel for reduction(+:sum)  \
            if(N>n_cutoff) num_threads(omp_get_max_threads())
   for(i=1; i<=N; i++)
     sum = sum + (double)i;
   
   printf("sum= %f\n",sum);
   
}
```

```
## PROGRAN ex2c.c (answer):

#include "omp.h"
#include <stdio.h>
#define N 272
long long tsc_timer(void);
int main(){

   long long k0, k1, kt=0;

   int   i;
   double sum = 0.0e0;

   k0 = tsc_timer();   

   #pragma omp parallel for reduction(+:sum)
   for(i=1; i<=N; i++)
     sum = sum + (double)i;

   kt = kt + tsc_timer()-k0;
   printf("Execution cost (clock periods) %ld\n",kt);
   
   
   printf("sum= %f\n",sum);
   
}
```

```
## PROGRAN ex2d.c (answer):

#include "omp.h"
#include <stdio.h>
#define N 272
#define NTRIALS 3
long long tsc_timer(void);

int main(){

   int   i,nt;
   long long k0, k1, kt=0;
   double sum = 0.0e0;
   
   k0 = tsc_timer();
   #pragma omp parallel
   if(omp_get_num_threads() < 0) printf("Warmup from %ld\n", omp_get_num_threads() );
   kt = kt + tsc_timer()-k0;
   printf("First-Time warmup Parallel Overhead (CP) %ld\n",kt);
   
   kt=0;
  for(nt=1; nt<=NTRIALS; nt++){
     k0 = tsc_timer();
  
     #pragma omp parallel for reduction(+:sum) 
     for(i=1; i<=N; i++) sum = sum + (double)i;
  
     if(sum == 0.0e0) printf("Hmmm\n"); //don't optimize away the reduction.
     kt = kt + tsc_timer()-k0;
  }   
  printf("Use for actual    Parallel Overhead (CP) %ld\n",kt/NTRIALS);
   
}
```
