##  if clause and clock period counter

## BACKGROUND
The "if" clause argument can be a conditional expression
which can turn on or off the application of the directive
at runtime.  It is a good way to determine if it is
reasonable to perform a loop with worksharing or no.

You can use a clock period counter, to get an accurate
estimate of the overhead of a parallel construct.

# Exercise

A.)  Review the basic reduction code:

     ex2.F90 

     What would happen if the initial value of sum is not 0.0e0?

A.)  Review the basic reduction code:

     ex2.F90 for comparison.
     What would happen if the initial value of sum is not 0.0e0?

B.)
     copy ex2.F90 to ex2b.F90

     In ex2b.F90 calculate the following cutoff with this statement:

   1 n_cuttoff = 20000 + N/omp_get_num_procs()   !or vvv
   a n_cuttoff = 20000 + N/omp_get_max_threads()

     (where N is the number of iterations).

   b Use omp_get_num_procs() as an argument to a num_threads clause.
   b Use omp_get_max_threads() as an argument to a num_threads clause

   c include an "if clause" to execute the loop N>ncuttoff
  
   d Compile and run:
 ``` 
     ftn -fopenmp ex2b.F90
     export OMP_NUM_THREADS=64
     ./a.out 
 ``` 

     See code ex2b.F90 below AFTER you are finished doing the
     modifications and test yourself.
     What would happen if the initial value of sum is not 0.0e0 here?

C.)
     The 20000 base is just a first estimate for the cutoff base.
     By measuring the cost of the overhead, we can determine a better value.
     Look over the timer.c code.  ts_timer() gets the value in the
     Time Stamp register (number of clock periods (Hz) used).

     The cores run nominally at 1.4GHz (2.1 for SKX).  
     How many seconds are in a clock period?

     Copy ex2.F90 to ex2c.F90.
     Use the ex2c.F90 code to:
            determine a base serial execution cost, and then
            the overhead of a parallel region

            (Later, we will evaluate the cost of forking threads for the first time).

       Make these changes to the code:
```
       integer, parameter :: N=272
       integer, parameter :: KI8 = selected_int_kind(15)
       integer(KI8), external :: tsc_timer
       integer(KI8)           :: k0, k1
       ...
       k0=tsc_timer()
         <parallel loop>
       k1=tsc_timer()
       print*,"Execution cost (clock periods)",(k1-k0)
```


   1.) Serial execution

       cc -c timers.c; 
       ftn ex2c.F90 timers.o
       ./a.out

       How many clock periods does it take to run the reduction serially.

   2.) Parallel execution

       Now compile and run it on 68 cores:
```
       ftn -fopenmp ex2c.F90 timers.o
       export OMP_NUM_THREADS=64
       ./a.out
```
   
       How many seconds does it take to run the reduction in parallel.
       (use 1.4GHz for KNL or 2.1GHz for SKX; X-clockperiods/1.4x10^9), etc.)
       Wow!! This is long.  What is the problem.
       (Hint, could this be due to a one-time cost of starting a the OpenMP
        runtime, and loading and *.so files?)

       (Check your results against those below for ex2d.F90 in the next exercise.)

   3.) Now, look at ex2d.F90 below.
       It measures the initial start up, and does and calculates
       a true overhead for forking.

```
       ftn -fopenmp ex2d.F90 timers.o
       export OMP_NUM_THREADS=64
       ./a.out
```

       What is the true cost of the parallel forking?

   4.) Try this on another platform (e.g.Skylake if you have been using KNL)
       What is the initial fork cost on this system?

    5.) Experiment using fewer cores?
        Does the startup depende upon the number of cores?


## PROGRAN ex2b.F90 (answer):
```
program ex2b
use omp_lib

integer, parameter :: N=25000
integer            ::  n_overhead=20000

double precision   :: sum = 0.0d0

!   the "!$" line is seen only when the -qopenmp option is used

!$ n_cutoff = n_overhead + N/omp_get_max_threads()

   !$omp  parallel do reduction(+:sum) &
   !$omp&  if(N>n_cutoff) num_threads(omp_get_max_threads())
   do i = 1,N
     sum = sum + i
   end do

   print*,"sum=",sum

end program
```

## PROGRAN ex2c.F90:

```
program ex2c
use omp_lib

integer, parameter :: N=272
integer, parameter :: KI8 = selected_int_kind(15)
integer(KI8), external :: tsc_timer
integer(KI8)           :: k0, k1

double precision   :: sum = 0.0d0

   k0=tsc_timer()

   !$omp  parallel do reduction(+:sum)
   do i = 1,N
     sum = sum + i
   end do

   k1=tsc_timer()
   print*,"Execution cost (clock periods)",(k1-k0)

   print*,"sum=",sum

end program
```

## PROGRAM ex2d.F90

```
program ex2d
use omp_lib
integer, parameter :: KI8 = selected_int_kind(15)
integer, parameter :: NTRIALS=3, N=172

double precision :: sum=0.0d0

!unsigned long long  tsc_timer_(void){ return  tsc(); }
integer(KI8), external :: tsc_timer  
integer(KI8)  k0, k1


   k0=tsc_timer()
   !$omp  parallel
!$ if(omp_get_num_threads() < 0) print*, "Warmup from ", omp_get_num_threads()
   !$omp  end parallel
   k1=tsc_timer()
   print*,"First-time, warmup, overhead         ",k1-k0


do nt = 1,NTRIALS

   k0=tsc_timer()

   !$omp  parallel do reduction(+:sum)
   do i = 1,N
     sum = sum + real(i)
   end do
   if(sum == 0.0e0) print*,"Hmmm" !don't optimize away the reduction.

   k1=tsc_timer()

enddo

   print*,"Use for actual Parallel Overhead (CP)",(k1-k0)/NTRIALS

end program
```
