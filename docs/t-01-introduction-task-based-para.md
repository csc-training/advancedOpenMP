---
title:  Introduction to task based parallelism
author: CSC Training
date:   2024
lang:   en
---

# Introduction to task based parallelism {.section}

# Worksharing Review

- Parallel regions are created by forking  a team of threads.
- `omp for/omp do`  constructs are placed inside parallel regions.
    - The loop iterations are partitioned.
    - Each thread has its own data enviroment.
    - Program executions pauses until all threads reached the end of the parallel region .


<div class="column">
```c
#pragma omp parallel for schedule(static)
 {for(i=0;i<n;i++) 
      foo(...,i);}
```
</div>
<div class="column">
```fortran
!$omp parallel do schedule(static)
  do i=1,n; foo(...,i); enddo
!$omp end parallel do
```

# Pros

- Easy to implement for loop-based parallelism where iterations can be evenly distributed across threads.
- Ideal for situations where the workload is uniform, such as in simple loops with predictable iteration counts.
- OpenMP provides different automatic load balancing via scheduling options (static, dynamic) to balance the load across threads, improving performance when work distribution is uneven.
- `#pragma omp for/!$omp do` have very low overhead.

# Limitations

- `omp for/omp do` is not well-suited for recursive algorithms  or irregular parallelism.
- The implicit barriers at the end of the loop can cause delays, especially if some threads finish their work much earlier than others.
- The developer has less control over the execution order and the distribution of work compared to tasking.
   - There is only First In, First Out (FIFO) queue available,  i.e no dependencies.

# `omp sections` 
- Before OpenMP 3.0, the only way was using **sections** construct.
 


<div class="column">
```c
#pragma omp parallel
#pragma omp sections
{
    #pragma omp section  
    {
        foo_1(...); 
    }
    #pragma omp section  
    {
        foo_2(...); 
    }
}

...
```
</div>
<div class="column">
```fortran
!$omp parallel 
!$omp sections

    !$ omp section  

        foo_1(...)

    !$omp section  

        foo_2(...)

!$omp end sections
!$omp end parallel 
```
</div>

# Terminology 

 - A **task** is specific instance of *executable code*, *its data environment*.

 - `#pragma omp for/!$omp do` creates `OMP_NUM_THREADS` **implicit task**s.

<div class="column">
```c
#pragma omp parallel for schedule(static)
 {for(i=0;i<n;i++) 
      foo(...,i);}
```
</div>
<div class="column">
```fortran
!$omp parallel do schedule(static)
  do i=1,n; foo(...,i); enddo
!$omp end parallel do
```
</div>

 - **Explicit task**s are tasks which not an **implicit task**s.
    - They are created by user via constructs (task., taskloop, target task).

# Execution model

 - Creates a parallel region which forks a team of threads. 
 - Tasks can be created by a single thread or several.
    - Each execution of a task construct generates a new task.
 - Tasks can be nested. 
 - Tasks may be executed *immediate*ly or can be *deffered*.
    - The runtime decides when.
 - All threads in the parallel region can execute tasks. 


# Basic Tasking


<div class="column">
```c
#pragma omp parallel 
#pragma omp masked // or single
while(condition){
      #pragma omp task [clause[[,] clause]...]
        foo(...,i);  
    }


  
```
</div>
<div class="column">
```fortran
!$omp parallel 
!$omp masked ! or single
do while(condition)
      !$omp task [clause[[,] clause]...]
        foo(...,i);
      !$omp end task
enddo
!$omp end masked
!$omp end parallel
```
</div>

# Task clauses

<div class="column">
 - private(list)
 - firstprivate(list)
 - shared(list)
 - default(shared|none)
 - in-reduction(red-op:list)
 - allocate([allocator:]:list)
 - detach(event-handler)
</div>
<div class="column">
- if(expression)
- mergeable
- final(scalar-expression)
- depend(dep-type:list)
- untied
- priority(value)
- affinity(list)
</div>

# Data  Scoping
 - Local variables are private
 - Static and global variables are shared
 - *private* variables are inheriatated as *firsprivate*
 - *shared* attribute is inherited. 

# Task Synchronization: **taskwait**


<div class="column">
```c
#pragma omp parallel 
#pragma omp masked // or single
while(condition){
      #pragma omp task [clause[[,] clause]...]
        foo(...,i);  
    }


  
```
</div>
<div class="column">
```fortran
!$omp parallel 
!$omp masked ! or single
do while(condition)
      !$omp task [clause[[,] clause]...]
        foo(...,i);
      !$omp end task
enddo
!$omp end masked
!$omp end parallel
```
</div>


# Summary

- OpenMP tasks
