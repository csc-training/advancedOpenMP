# reduction clause on a simd construct

## BACKGROUND
OpenMP can handle SIMD reductions in a "vectorizable" way, and knows how to
use private variables.
Use vector reporting to determine why vectorization doesn't occur
Use an approriate simd directive with an appropriate reduction clause
to vectorize the loop

## EXERCISE
1.)

    The loop doesn't vectorize.
    Compile with vector reporting.

   FRONTERA:
```
     icc   -fopenmp -c reduce.c   -qopt-report-phase=vec -qopt-report-stdout
     ifort -fopenmp -c reduce.f90 -qopt-report-phase=vec -qopt-report-stdout
```

   STAMPEDE:
```
     icc   -fopenmp -c reduce.c   -qopt-report-phase=vec -qopt-report-file=stdout
     ifort -fopenmp -c reduce.f90 -qopt-report-phase=vec -qopt-report-file=stdout
```

   LUMI:
```
     cc  -fopenmp -c reduce.c    -fsave-loopmark -O2
     ftn -fopenmp -c reduce.f90  -hlist=m        -O2
```

    Review analysis: Discover why loop did not vectorize

    LUMI: 
          cc: loop is not vectorized
         ftn: loop is     vectorized
   
2.)

    Insert SIMD directive to force vectorization
    Compile with -qopenmp and vector reporting
    Review analysis --confirm vectorization

    LUMI:
         cc: loop was vectorized.
        ftn: No change in vectorization
       

3.)
    FRONTERA and STAMPEDE ONLY:
    NOW add "–qopt-report=3", and determine what the vector speedup is.

    C code:
    Try replacing prototype
```
          double fun(double a); 
```
    with a real function:
```
          double fun(double a){return a*a;}
```

    F code:
    Add this function at the top of the code (described by the func interface):
```
      double precision function fun(b)
         double precision  :: b
         fun=b*b
      end function
```
   Now, compile again with -qopt-report=3

   How must faster is the estimated vector speedup? __________
   Will  the function make a difference in the estimated speedup?_________
  

4.) QUESTIONS:
    Why would it be difficult to SIMDize a reduction? _______________



