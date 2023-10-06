# OpenMP Affinity 

##BACKGROUND
You will:
* Set up OpenMP affinity environments (with OMP_PROC_BIND & OMP_PLACES)
* Execute amask_omp to discover the setting
* Answer questions

##Exercises

Before you begin, set up a partition/C environment with the module command,
put the path of amask_omp  in your PATH env. var., and
then get on a partition/C node with a srun command.
```
     ml LUMI/23.03; ml partition/C

     export PATH=/project/project_462000390/cpu_bin:$PATH

     srun -N 1 -n 1 -A project_462000390 -p debug -t 00:30:00 --cpus-per-task=128 --pty bash

```
or
```
    source /project/project_462000390/sourceme_cpu

    mlc
    idevc

```

```
********  IMPORTANT
    "Hyperthreading" is turned on in LUMI/C.
    In the amask_omp utility
    The first  HW threads are reprsented on the first   lines (---- lines)
    The second HW threads are reprsented on the secondt lines (==== lines)
    And the header numbers are core values.
       thrd |    0    |   <- core-id
       0000 0----------
            ==========
       0001 -2---------
            ==========
    However, the Cray omp runtime does not use/accept the process numbers but
    only the core-id.  With this strangeness (which needs to be resolved)
    amask is  only showing occupation in the 1st HW thread(--- lines).  
    For these experiments, just ignore the second empty lines (====) and
    assume the first lines are core occupations.
```


1.)
   Set the threads close to each other for a few PLACES, using  OMP_PROC_BIND = close,
   and make sure it is working as expected.
```
          export OMP_NUM_THREADS=4
          export OMP_PLACES='{0},{4},{8},{12},{16},{20},{24},{28}'
          export OMP_PROC_BIND=close

          amask_omp                       #This shows the core view
```

    a.) What core-ids do the 4 thread land on?  __ __ __ __



2.)
   Now, just change OMP_PROC_BIND to spread, and run amask:
```
          amask_omp
```
    a.) What proc-ids do the 4 threads land on?  __ __ __ __

3.)
   Now, set display the default for openmp
```
          export OMP_NUM_???????
          amask_omp
```
   What is OMP_PLACES set to?
   LUMI/C:
   What is the "auto" for PROC_BIND?
   How can you find out about this?  Hint: man pages.
   Is "man intro_openmp" your friend.  Look for PROC_BIND
   (Maybe just get a copy: man intro_openmp > see.intro_openmp.)

4.) 
   LUMI/C ONLY
```
   // test code:
   #include <omp.h>
   #include <stdio.h>
   int main(){
   #pragma omp parallel
   printf("%d thread\n",omp_get_thread_num());
}
```

   Compile this trivial test code.  cc -fopenmp test.c
   Now, unset OMP_NUM_THREADS OMP_PROC_BIND.
   So, NO threads are set, right?
   What would you expect the default to be?
```
   unset OMP_NUM_THREADS OMP_PROC_BIND OMP_DISPLAY_ENV
   ./a.out
```
   It appears to be set to 128.
   Now set OMP_DISPLAY_ENV to TRUE and run.
   What does that say?  (1?)
     



Frontera ONLY. 
(Htop is not set up on LUMI, and the wait option  does not work on LUMI yet.)

Runtime Viewing
In your idev window, execute:

        amask_omp -w 60

In another window execute the following, to see the thread occupation:

        module htop        #required at TACC, others sites may not have htop
        htop               #control-c to exit

Select one of the threads, and then type "a", you will see the affinity mask.
Hit escapte to leave affinity mode.  (Note, you can reset the affinity here!)

Execute:
       show_affinity       #@TACC only, gives a listing of the affinity


Execute:
       top
       hit the "1" key to get the threads. 


