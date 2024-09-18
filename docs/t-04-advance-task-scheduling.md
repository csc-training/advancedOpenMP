---
title:  Advanced Task Scheduling 
author: CSC Training
date:   2024
lang:   en
---

# Advanced Task Scheduling{.section}



# Controlling tasks

 - The **task** construct supports several clauses that can be used to influence the tasks scheduling:
    - **if**
    - **final**
    - **meargeable**
    - **untied**
    - **priority**
    - **affinity**
 - The **taskyield** directive indicates that the task can be suspended in favor of execution of a
different task. 


# Controlling tasks
 
 - Tasks can be suspended and continued.
    - By default tasks are *tied* a thread, but this can be overwritten.
 - Cut-off procedures can be employed using:  **if**, **final**, **meargeable** clauses.
 - It is possible to asign different **priority** to the tasks.
 - With the **affinity** clause, it is possible to bind tasks to specific threads based on the data location in the system.
 - One can introduce own scheduling points using the **taskyield** directive.

# if Clause

 - When `if(false)` an *undeferred* task is created.
 - The new task will be executed imediately and the parent task is suspended meanwhile.
 - Useful for avoiding  creation of (too small) tasks and  debugging.
 - The data-sharing clauses are still honored!!!

<div class=column>
<small>
```c
int foo(int x) {
    int res = 0;
    printf("entering foo function\n");
    #pragma omp task shared(res) if(false)
    {      
        res += x;
    }
    printf("leaving foo function\n"); 
}
```
</small>
</div>

<div class=column>
<small>
```fortran
subroutine foo(x)
  integer :: x, res = 0 
  print *, "entering foo function"
  !$omp task shared(res) if(.false.)
    res = res + x
  !$omp end task
  print *, "leaving foo function"
end subroutine foo
```
</small>
</div>


# final Clause
 - When `final(false)`  new task is created and executed normally but all its child tasks will be executed immediately
by the same thread.
 - Useful for avoiding create too many tasks in nested tasks/recursive applications
 - The data-sharing clauses are still honored!!!

<div class=column>
```c
#pragma omp task final(e)
{
    #pragma omp task //B
    { … }
    #pragma omp task //C
    { … #C.1; #C.2 … }
    #pragma omp taskwait
}
```
</div>

<div class=column>
![](img/final_clause.png){.center width=55%}
</div>


# mergeable Clause
 - **meargeable** is clause of the **task** construct to reduce the overhead of task creation
 - It allows tasks to be merged with their parent task.
 - It hints to the compiler that the task does not rely on being executed independently or concurrently.
 - Tasks with the mergeable clause may be executed immediately or merged, depending on the compiler.
 - **Unfortunately, there are no OpenMP commercial implementations taking advantage of final neither mergeable.**


# priority Clause
 
 - It is possible to specify  a priority value when creating a task.
    - ` omp task priority(pvalue)` 
    - the higer pvalue the earlier the task gets schedules.
    - once a thread becomes idle, gets one of the highest priority tasks.



<div class=column>
```c
 for ( i = 0; i < SIZE; i++) {
    #pragma omp task priority(1)  
    { code_A; }
 }

 #pragma omp task priority(100)
 { code_B; }
```
</div>

<div class=column>
```fortran
 do i=1,SIZE
    !$omp task priority(1)  
      code_A
    !$omp end task
 enddo 
  !$omp task priority(100)
    code_B
  !$omp end task
```
</div>


# affinity Clause
 - The **affinity** clause indicates to execute the task on the thread closer to physical data location.
 - Improves data locality and  reduces remote memory accesses.
 - Decreases runtime variability
 - If a thread is under-utilized, task stealing is still expected.


<div class=column>
```c
 #pragma omp task affinity (list)
```
</div>

<div class=column>
```fortran
 !$omp task affinity (list)
```
</div>



# untied Clause

 - By default the tasks are **tied** to the same thread in which they start the execution.
 - The **untied** clause indicates that after suspension the task can moved to another thread if it is beneficial.
 - Thread based features: *thread-id*, *threadprivate*, ... should not be used.
 - Unfortunately not alll implementtions obey this.

# Task Scheduling Points
 - A program may generate so many tasks that the internal data structures managing tasks overflow.
 - Task switching can only occur at Task Scheduling Points (TSP). 
    - implicit scheduling points: creation, completion, at the end of a **taskgroup** or  **barrier**, in a **taskwait** region, in and around regions associated with **target** constructs.
    - explicit scheduling point: in a **taskyield** region.
 - At a task scheduling point the following can happen:
   - Begin execution of a **tied** or **untied** task.
   - Resume any suspended task (**tied** or **untied**) .

# taskyield Directive 

  - The **taskyield** directive signals to the runtime that it is willing to pause execution and allow another task to run
  - This improves load balancing and can prevent starvation or deadlocks by allowing the runtime to interleave task execution.

# taskyield and untied example

<div class=column>
```c
 #pragma omp parallel
 #pragma omp single
 {
    #pragma omp task untied
    {
        foo();
        #pragma omp taskyield
        bar()
    }
 }
```
</div>

<div class=column>
```c
#include <omp.h>
void something_useful();
void something_critical();
void foo(omp_lock_t * lock, int n)
{
    for(int i = 0; i < n; i++)
    #pragma omp task
    {
        something_useful();
        while( !omp_test_lock(lock) ) {
        #pragma omp taskyield
        }
    something_critical();
    omp_unset_lock(lock);
    }
}
``` 
</div>


# Summary
 - **Cut-off strategies**: 
    - **task** clauses **if**, **final**, **meargeable**.
    - This reduces overhead but also reduces parallelism. 
 - **Task Scheduling**: 
    - **task** clauses **untied**, **priority**, **afffinity**
    - The **taskyield** directive indicate a point where  task can be suspended in favor of execution of a
different task. 
