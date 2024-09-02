---
title:  Introduction to task based parallelism
author: CSC Training
date:   2024
lang:   en
---

# Introduction to task based parallelism {.section}

# `omp for/omp do` Worksharing 

- Parallel regions are created by forking  TEAM OF THREADS.
- Worksharing constructs are placed inside parallel regions.
    - LOOP ITERATION ARE PARTITIONED
    - DATA ENVIRONMENT
    - IMPLIED BARRIERS
    - work is assigned (implicitely) to the threads.

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

# Terminology 

 - A **task** is specific instance of *executable code* and *its data environment* that can scheduled for execution by threads.

 - `#pragma omp for/!$omp do` create so-called **implicit task**s.

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

- `OMP_NUM_THREADS` **implicit task**s will be created.
    - each executing `foo(...,i)` for `i=thread_ibeg:thread_iend`.


 - **Explicit task** is a task not an implicit task.

# Summary

- OpenMP tasks
