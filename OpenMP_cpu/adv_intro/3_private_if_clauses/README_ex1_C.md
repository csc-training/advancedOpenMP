# private clause with a work index

## BACKGROUND
The present ex1.c code creates a parallel region,
and passes the thread number to a routine to print it.
(You can compile and run it. --not necessary--)

```
   #pragma omp parallel
   {
     foo(omp_get_thread_num());
   }
```

## Exercise
Copy ex1.c to ex1b.c and make the following changes:

1.)  Make "id" a variable in the main program.
2.)  Assign id in the parallel construct using the omp_get_thread_num() api function
     and pass it as an argument like this:

```
      int id;
      #pragma omp ...
      {
         id = omp_get_thread_num();
         foo(id);
      }
```

3.)  Compile and run the code:

```
     cc  -fopenmp ex1b.c       #LUMI
     icc -fopenmp ex1b.c       #TACC
     export OMP_NUM_THREADS=64
     ./a.out | sort
```

     What happened?  (Probably the code works-- but is it correct? **
     (Oops, forget to make id a private variable?)
     If so, use the private clause to make id private (recompile & run)
     Do not look at ex1c.c below until you have tried your exe1b.c execution.

4.)  Now copy ex1c.c below into a file called ex1c.c, compile and run. 
     It illustrates the idea of slowing down threads to convince
     yourself that a race condition exists on the id variable.
     Look at the code carefully, and explain what is happening in this code.

     Hmmm, quess why  foo(omp_get_thread_num()) does the right thing?

 
``` 
// ex1b.c
#include "omp.h"
#include <stdio.h>
void foo(int);

int main(){
   int id;
   #pragma omp parallel
   {
     id = omp_get_thread_num();
     foo(id);
   }
}

void foo(int id){
  printf("thrd_id %0.3d\n",id);
}
```
```
// ex1c.c
#include "omp.h"
#include <stdio.h>
void foo(int);

int main(){
   int id;

   #pragma omp parallel
   {
    if(omp_get_thread_num() > 0){
      id = omp_get_thread_num();
      system("sleep 1");
    }
    else{
      id = omp_get_thread_num();
    }
    foo(id);
   }
}

void foo(int id){
  printf("thrd_id %0.3d\n",id);
}
```
