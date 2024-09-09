# SIMDIZE a loop with pointers

## Background
The loop in this example is not vectorize because pointers may be
aliasing overlapped regions.

Assume  there is no overlapping in the variable accesses.
Use vector reporting to determine why vectorization doesn't occur.
Use  the simd directive to vectorize the loop.

1.)
    Compile with vector reporting.

   FRONTERA:
```
     icc   -fopenmp -c ptrs.c   -qopt-report-phase=vec -qopt-report-stdout
     ifort -fopenmp -c ptrs.f90 -qopt-report-phase=vec -qopt-report-stdout
```

   STAMPEDE:
```
     icc   -fopenmp -c ptrs.c   -qopt-report-phase=vec -qopt-report-file=stdout
     ifort -fopenmp -c ptrs.f90 -qopt-report-phase=vec -qopt-report-file=stdout
```

   LUMI:
```
     cc  -fopenmp -c ptrs.c   -fsave-loopmark
     ftn -fopenmp -c ptrs.f90 -hlist=m 
```

    Review analysis: Discover why loop did not vectorize

    FRONTERA/STAMPEDE F/C: loops is not vectorized
    LUMI              F/C: loops is not vectorized
                        F: loops is not vectorized (if -O2 used)
                        C: loops is     vectorized (if -O2 used)
   
 
   
2.)

    Insert SIMD directive to force vectorization
    Compile with -qopenmp and vector reporting
    Review analysis to confirm vectorization

    FRONTERA/STAMPEDE F/C: loop is vectorized
    LUMI                F: loop is vectorized
                        C: loop is not vectorized

    LUMI                F: vectorizes for "-O2"
                        C: vectorizes for "-O2"

    Q: Does restrict keyword allow vectorization or not?   __________________
   
    Theoretically, how much faster should the vectorized loop execute?  _____

3.)
  Remove the OpenMP Directive in the code.
  Now add the "restrict" keyword to every call pointer argument 
  (e.g. float* a --> float* restrict a)

  Q: What option on the compiler is required to honor the restrict attribute? -------
  Q: Does restrict keyword allow vectorization or not?                        -------
  https://stackoverflow.com/questions/7328463/how-to-tell-a-c-or-a-c-compiler-that-pointers-are-not-aliased


