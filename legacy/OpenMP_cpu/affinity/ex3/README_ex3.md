#

## BACKGROUND

## Exercises

1.) experiment with 128 threads, 128 places, each placed a core

    Unset all OpenMP Affinity variables withe the "unset" command.
```
        unset OMP_PROC_BIND
        unset OMP_PLACES
        unset OMP_DISPLAY_ENV
    or
        unset OMP_PROC_BIND OMP_PLACES OMP_DISPLAY_ENV
```
    FYI: It also a good idea to determine if any are set by the system,
    Some sites set OMP_NUM_THREADS to 1, so that it is not set to
    an implementation default. To find out about any OpenMP variables,
    it is easy enough to determine any are set (env | grep OMP_)
    

```
        export OMP_NUM_THREADS=56    #Frontera
        export OMP_NUM_THREADS=128   #LUMI/C
        amask_omp
```

    Would it be appropriate to think that the affinity you observed is
    the same on all systems?   Let's investigate some more
    (Note, if see the pattern and don't want to wait for the display
    to finish, just ^c out of the amask_omp execution.)

    LUMI/C
```
        thrd |    0    |   10    |   20    |   30    |   40 ...
        0000 0============================================= ...
             ---------------------------------------------- ...
        0001 =1============================================ ...
         .   -----------------------------------------------...
         .
```
    Frontera:
```
        thrd |    0    |   10    |   20    |   30    |   40    |   50    |
        0000 01234567890123456789012345678901234567890123456789012345
        0001 01234567890123456789012345678901234567890123456789012345
         .
         .
```
    Determine what the runtime implementation does?
    How would you do that?   Hint:  How are the OpenMP ICV values displayed?

```
        export OMP_DISPLAY_ENV
```
    LUMI/C:     OMP_PROC_BIND is auto
    FRONTERA:   OMP_PROC_BIND is false

    Does that explain the difference?

    LUMI/C:  Set OMP_PROC_BIND to FALSE and evaluate the affinity with amask.


2.)
    Now, let's bind each thread to a single core. 
```
        export OMP_PROC_BIND=TRUE
        export OMP_PLACES=cores
        amask_omp
```

    Note that each thread_number in the sequence 0, ...128 
    is assigned to a unique numbered processor (core number).

    FRONTERA: (Cascade Lake) 
    (Unfortunately, Intel does not assign them sequentially.
    For now, assume that cores are identical, and that it
    therefore does not matter.)

    Do you see a pattern?  _______   Does it make sense?_______
    See class notes.

    LUMI: They are assigned sequentially (as shown in 1.).

2.)  Use 1/2 the threads (Lumi/C: 64, Frontera/28) and spread out
```   
        #2a
        export OMP_NUM_THREADS=64  #Lumi/C
        export OMP_NUM_THREADS=28  #Frontera

        export OMP_PROC_BIND=spread

        export OMP_PLACES=cores
        amask_omp
```

     Is the selection every-other-one of the results shown in 1.)  above ? ________

     Now bind each threads to 2 adjacent cores:

     FRONTERA:  processor numbers are even/odd on socket 0/1
```
        #2b
        export OMP_PLACES='{0,2}:14:4,{1,3}:14:4'
        amask_omp
```
     LUMI/C  processor numbers are sequential across sockets
     0-63 on socket 0, and 64-127 on socket 1
    
```
        #2b
        export OMP_PLACES='{0,1}:32,{64,65}:32'
        amask_omp
```

     When using a thread count which is 1/2 the core count:
     What is the obvious difference between 
     assigning a thread to every other core without a OMP_PLACES list (#2a),
     and assigning a thread to a pair of cores, with the explicit
     OMP_PLACES list (#2b).
     

     Does the explicit place list in the PLACE variable allow more floating?


3.) LUMI: Given that you want to allow 2 processes for background
    processes, how could you set up (128-2)/2=(126)/2=63
    threads  on each socket.

    Make an appropriate OMP_PLACES list for this.
    and check your results.  (See ans_Questions in solution dir.)
```
        export OMP_PLACES='{0}:63,{64}:63'
```
    Confirm what you did by looking at thread no 62 and 63.  Does it make sense 
    Unset OMP_PLACES and look at the mask around thread 64.  What is the
    difference?  (Note: using the place will probably do a much better job
    of leaving a core free on each socket.)

4.) LUMI:
    Given that you will run 8 threads, and you want to bind each 
    thread to a single NUMA node (any one of the 16, listed above,
    what would be the ways to do this with OMP_PLACES? 
    Do it two different ways: 

    1.) create a list with 8 places, using the 1st core in each NUMA node.
    (You could use any of the cores ids within each of the NUMA nodes.)

    2.) A single expression which uses the 1st core in each NUMA node
    created by making 8 places from the "{0}" place with a stride of 16.
    Check both place lists with amask_omp.            
    Can you do this for OpenMP threads without using OMP_PLACES?
```
        export OMP_NUM_THREADS=8
        export OMP_PLACES='{0},{16},{32},{48},{64},{80},{96},{112}'
        export OMP_PLACES='{0}:8:16'
```
    How would you do this and allow floating on any of the 16 cores
    in a numa node?  Will both of the following work?
```
        export OMP_PLACES='{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}:8:16'
        export OMP_PLACES='{0:16}:8:16'
```

5.) LUMI 
    Try using abstract places with OMP_PLACES, and check your resuls.

    for putting two threads, one on each socket:
```
        export OMP_NUM_THREADS=2
        export OMP_PLACES=
```
    Would this list "{0}:64,{64}:64" have produced that same result? Try it.

    Use the "numa" abstract list to put a single thread on each of the 8 numa nodes:
```
          export OMP_NUM_THREADS=8
          export OMP_PLACES=
```
    What is possibly wrong with this abstract place list?

    What is the differnce between using "numa_domains" and
    using "{0}:8:16" as described in an earlier experiment
    (Uh, numa_domains came after 5.0, and isn't implemented yet 2023/10/09.)

    Would just setting PROC_BIND=spread and OMP_NUM_THREADS=8
    (and unset OMP_PLACES) have done the same as using numa?

    The amask -v k option shows the kernel map (0-255 procssors numbers 
    arranged along a single line., try using it.
