# Tasks using the counter of the generating task.

## Background

Dependences between tasks are often build upon the requirement of data to be 
synchronized because tasks that need to read or write to the data;  a "flow
dependence" is needed to order the task executions.  

OpenMP task dependences are ideal for handling these types of cases that
appear in graphs. The one limiting factor is that the dependences must be
sequentially created (one task generation follows the previous tasks, etc.).  
This sequential formation of dependencies is actually optimal for handling
the number of locks and barriers in the OpenMP runtime required for the scheduling.

(This is actually fine for many cases that create dependences in a loop 
structure, and often the way you would want to generate dependences.  OpenMP
is working on dependences with a more robust "global", non-sequential mechanism.) 

The INOUT dependence has the read and write dependence types. 
It is included for completeness, because and OUT supplies the
same functionality.  In terms of "flow" it specifies that a read
is performed as well as a (following) write.


## Exercises

In this exercise you will include a INOUT (R/W) dependence in a task.
Also, you will create your own code which creates dependences in a loop.


1.) Read, compile and execute graph.c/F90  to see the expected values of
    the a,b,c,d,e variables at various points within the code.
```
      ftn -fopenmp graph.F90  -o a.out_graph
      or
      cc   -fopenmp graph.c    -o a.out_graph
      
      export OMP_NUM_THREADS=8
      ./a.out_graph
```
    Copy graph.c|F90  to graph_new.c|F90.
    Next, modify graph.c/F90  to make T4 dependent upon the variable "e" from
    T2, such that T4 reads the value, and adds 5 to it. Also
    make T5 dependent on the e value produced by T4.  In T5 print the
    value of e (what type of dependence is this relative to T4's e?).

    One would naturally make the dependence type inout for e in T4 and T5.  
    Could one have simply used "out" in these cases and created the
    same effect?

    How does the change affect the concurrent execution of tasks within graph?
    (Draw a diagram and explain.)
```
      ftn -fopenmp graph_new.F90  -o a.out_graph_new
      or
      cc  -fopenmp graph_new.c    -o a.out_graph_new
      
      export OMP_NUM_THREADS=8
      ./a.out_graph_new
```

2.) partial.c/F90 contains integers in an array, a.  It adds the
    values, to form a sum.  However, in the sequence of adding
    the values, if it finds a 0, it should let the previous tasks complete,
    and print out the partial sum (up to that point).  

    Review partial.c/F90 and determine the
    dependence type and data sharing required to make it print the
    correct partial sum within the tasking loop. 

    Hints:  use the single integer variable (id) to build up the dependences.
            Remember IN allows for simultaneous executions (reads)
            and an OUT or INOUT will cause ordering dependence (writes).

```
      ftn -fopenmp partial.F90  -o a.out_partial
      or
      cc  -fopenmp partial.c    -o a.out_partial
      
      export OMP_NUM_THREADS=16
      ./a.out_partial
```

FORTRAN OUTPUT:  Partial Sum at zero point at index=          50  sum=        1225
C       OUTPUT:  Partial Sum at zero point, index=49 sum=1225
