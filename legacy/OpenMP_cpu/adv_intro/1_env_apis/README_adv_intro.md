# OpenMP API routines and Environment Variables (EV)#

## BACKGROUND
Use the OpenMP Specification or Reference Guide** to determine the use
of OMP_DISPLAY_ENV, OMP_DISPLAY_AFFINITY arguments, and their APIs.  
** You can also use the course slides or the OpenMP Examples Document.

Make sure you understand what your getting from omp_get_num_threads and
omp_get_thread_num in and outside of a parallel region.

## Exercises

1.) 
    Look over adv_api(.c|f90), and finish the API calls in the
    parallel region to get the thread "count" and "id". TODO 1:

    Compile and run with 8 threads.
```
       CC -fopenmp env_api.c   |  ftn -fopenmp env_api.c
       export OMP_NUM_THREADS=8
       ./a.out
```
    Now, make a copy of the print statement and put it before
    the parallel construct.  Compile and run again.
    Is 1 correct for the thread count for the new print statement?

    What would you use outside of a parallel region to 
    get as many threads as there are cores?
    Try: omp_get_max_threads() and omp_get_num_procs().
         What does the Spec say about these?
         Use these with care, especially with hyperthreading!

2.)
    Now, set the OMP_DISPLAY_ENV OMP_DISPLAY_AFFINITY to
    TRUE, and run.

```
       export OMP_DISPLAY_ENV=TRUE OMP_DISPLAY_AFFINITY=TRUE
       ./a.out
```
    Look over the ICV list to see what the defaults are for
    THIS system.  
    What is the version of OPENMP Compliance?
    What is the  default scheduling policy?
    Note: Affinity is shown for the parallel region
    (what you may expect).

3.)
    
    Now, unset OMP_DISPLAY_ENV and OMP_DISPLAY_AFFINITY
    Call the omp_set_display_env and omp_set_display_affinity
    API routines before the parallel construct. <TODO 3:>
 
    Compile and run.  
    If you see "ld.lld: error: undefined symbol: omp_display_env";
    it means that omp_display_env() api isn't implemented.
    Is omp_set_display_affinity available on
    your system, remove the call?

    What region is the affinity display for?
