
# Tasks using the counter of the generating task.
    
## Background

The cntr#.F90 programs generate tasks within a while loop
using a single thread within a parallel region, like this:
```
    !$omp parallel    //Generic task loop generation
    !$omp single

       do while(){
          !$omp task
            ...
          !$omp end task

          cntr = cntr + 1
       end do

    !$omp end single
    !$omp end parallel
```

This is very unlike a worksharing loop that gathers the team of
threads to split up the iterations as chunks among the threads:
``
    !$omp parallel   //Generic worksharking loop
       ...

       !$omp do
       do i = 1,n
          ...
       end do
    !$omp end parallel
```

In a while loop that generates tasks, a counter/pointer value is needed
for providing a different counter or pointer value for each task.  Unlike a
worksharing loop that has a default private index value for each set of chunks
the tasks within a generating loop needs the counter or pointer not at the time
the task is generated, but at the time it is executed. (Remember, tasks are
thrown on a queue to be executed later.)

         Hence, it is often necessary to make variables firstprivate
         for the task (region).

ALSO, for the task region, variables that are not shared within the parallel
region, those that are private, become firstprivate by default.

For these exercises you should use 1 nodes:

```
        Frontera:   $ idev            -N 1 -tpn 56  For Tutorial Reservation

       Stampded2:   $ idev            -N 1 -tpn 48  For Tutorial Reservation
                    $ idev -p skx-dev -N 1 -tpn 48  Outside of Tutorial time

            SDSC:   $ srun -p debug   -N 1 --ntasks-per-node=24 -t 00:30:00 \
                                           --pty --wait=0 --export=ALL /bin/bash
            PSC:    $ interact        -N 1 --ntasks-per-node=28

            LUMI: Interactive Use
                  export PP=/project/project_462000390

                  partition C:
                  source $PP/sourceme_cpu
                  mlc                     #ml LUMI/23.03 ...  #see sourceme_cu
                  idevc                   #srun -p debug ...  #see sourceme_cpu

                  partition G:
                  source $PP/sourceme_gpu
                  mlg                     #ml LUMI/23.03 ...  #see sourceme_cu
                  idevg                   #srun -p debug ...  #see sourceme_cpu
```

General: Compute and run the counter.c/f90 code. It uses a counter variable (cntr) in the task block.


1.)
    Compile and run "as is", the incorrect code:

```
    ftn -fopenmp cntr1.F90 -o a.out.cntr1
    export OMP_NUM_THREADS=8
    a.out.cntr1
```

    Are the sequence of of cntr values printed correctly?  ___________
    Why? ______________________________________________


    Copy the cntr1.F90 to cntr1_ok.F90.
    Correct the problem, and rerun the code to convince yourself 
    that your correction will make it run as intended.


```
    ftn -fopenmp cntr1_ok.F90 -o a.out.cntr1_ok
    export OMP_NUM_THREADS=8
    a.out.cntr1_ok
```

    Are the sequence of of cntr values printed correctly?  ___________



2.)
   Look at the code in cntr2.F90.

   What is thread 0 doing different in the task? ____________________

   Compile and run "as is", the incorrect code:
```
    ftn -fopenmp cntr2.F90 -o a.out.cntr2
    export OMP_NUM_THREADS=8
    a.out.cntr2
```

    What are the expected values of cntr for thread 0 ?______________

    Copy cntr2.F90 to cntr2_ok.F90.
    Correct the problem, and rerun the code to convince yourself that your correction
    will make it run as intended.
```
    ftn -fopenmp cntr2_ok.F90 -o a.out.cntr2_ok
    export OMP_NUM_THREADS=8
    a.out.cntr2_ok
```


3.)
   Look at the code in cntr3.F90.  

   What is the conditional statement in the task doing? ____________________

   Why is the variable i automatically firstprivate?    ____________________

   Compile and run "as is", the incorrect code:
```
    ftn -fopenmp cntr3.F90 -o a.out.ntr3
    export OMP_NUM_THREADS=8
    a.out.cntr3
```

    What is the expected value of cntr for i = 50 ?______________

    Copy cntr3.F90 to cntr3_ok.F90.
    Correct the problem, and rerun the code to convince yourself 
    that your correction will make it run as intended.
```
    ftn -fopenmp cntr3_ok.F90 -o a.out.cntr3_ok
    export OMP_NUM_THREADS=8
    a.out.cntr3_ok
```

   What is the expected value for i = 50 now ?______________
