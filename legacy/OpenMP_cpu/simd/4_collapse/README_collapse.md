# collapse clause use in simd directive.

## BACKGROUND
Sometimes it is helpful to collapse loops before simdizing, particularly
if the nested loop is less than the SIMD length.

##  Exercises
Frontera: INTEL compiler:
Use vector reporting at level 3 to determine if 
collapsing the example loop can increase performance.

LUMI: Cray compiler
Use loopmark to determine the collapse action.

Use the #pragma omp simd collapse (C)  or !$omp simd collapse (f90) to vectorize loop.

1.)
    The loop doesn't vectorize for the Intel compiler!
    See this with vector reporting.
   
    FRONTERA:
```
     icc   -fopenmp -c collapse.c   -qopt-report=3 -qopt-report-phase=vec -qopt-report-stdout
     ifort -fopenmp -c collapse.f90 -qopt-report=3 -qopt-report-phase=vec -qopt-report-stdout
```

    STAMPEDE2:
```
     icc   -fopenmp -c collapse.c   -qopt-report=3 -qopt-report-phase=vec -qopt-report-file=stdout
     ifort -fopenmp -c collapse.f90 -qopt-report=3 -qopt-report-phase=vec -qopt-report-file=stdout   
```
   LUMI:
```
     cc  -fopenmp -c collapse.c   -fsave-loopmark -O2
     ftn -fopenmp -c collapse.f90 -hlist=m        -O2
```
   

   Frontera:  available with -3 reporting
   What is the default Vectorization [      ]speedup
   
2.)

   Now, collapse the two loops with a collapse clause
   in a simd directive.
   

    Frontera: Intel compiler with report level 3 estimates this for you.
    What is the estimated performance of vectorization now?
    SIMD and collapse outer loop:     [     ]speedup
    Should one collapse the loops?    [              ]
