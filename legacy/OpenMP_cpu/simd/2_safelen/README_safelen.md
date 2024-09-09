# Tasks using the counter of the generating task.

## Background
The important point about OpenMP simd directives is that they are portable.
The directives can specify an extent to which vectorization may be applied.
https://goparallel.sourceforge.net/wp-content/uploads/2015/09/TheParallelUniverse_Issue_22-Feature1.pdf

Use vector reporting/loopmark to determine why vectorization doesn't occur, the vector
length it uses if vectorized.
Use the safelen clause with the simd directive to specify that a length of 8 is safe.

## Experiments
1.) 

    The loop doesn't vectorize. (On Lumi cc compiler vectorizes with width of 4.)
    Compile with vector reporting.

   FRONTERA:
```
     icc   -fopenmp -c safelen.c   -qopt-report-phase=vec -qopt-report-stdout
     ifort -fopenmp -c safelen.f90 -qopt-report-phase=vec -qopt-report-stdout
```

   STAMPEDE:
```
     icc   -fopenmp -c safelen.c   -qopt-report-phase=vec -qopt-report-file=stdout
     ifort -fopenmp -c safelen.f90 -qopt-report-phase=vec -qopt-report-file=stdout   
```

   LUMI:
```
     cc  -fopenmp -c safelen.c   -fsave-loopmark -O2
     ftn -fopenmp -c safelen.f90 -hlist=m        -O2
```
   
    Review analysis: Discover why loop did not vectorize (Lumi cc determine the vector length.)
   
2.)

    Insert a SIMD directive to force vectorization,
    for a safe number of 8 elements to be proccessed
    in a SIMD (vector) unit.

    Even if the possible vector length is small, would
    it be reasonal to simdize it.
    
    Compile with -fopenmp and vector reporting
    Review analysis --confirm vectorization
   
   FRONTERA:
```
     icc   -fopenmp -c safelen.c   -qopt-report-phase=vec -qopt-report-stdout
     ifort -fopenmp -c safelen.f90 -qopt-report-phase=vec -qopt-report-stdout
```
   
   STAMPEDE2:
```
     icc   -fopenmp -c safelen.c   -qopt-report-phase=vec -qopt-report-file=stdout
     ifort -fopenmp -c safelen.f90 -qopt-report-phase=vec -qopt-report-file=stdout
```
   If you remove -qopt-report-stdout/-qopt-report-file= -- output will go to ptrs.optrpt file

   LUMI:
```
     cc  -fopenmp -c safelen.c   -fsave-loopmark -O2
     ftn -fopenmp -c safelen.f90 -hlist=m        -O2
```

   # Review analysis --confirm vectorization or more unrolling (for better or worse)

   QUESTIONS:
          FRONTERA:
          Theoretically, how much faster should the vectorized loop execute?  _____X
          What happens if you remove -fopenmp from the compile line
          for compilation of the updated code in Step 2:  __________________________

          LUMI:
            With the simd directive, how much more were the loops unrolled.
                                                      For cc:
                                                     For ftn:

            (Note, while the behavior here might not have changed much, on another
                   system it might be significant.)


          GENERAL
          When you forget what the compiler openmp option is, find out from compiler help!
          What command would you use to obtain the available compiler options ____________?

