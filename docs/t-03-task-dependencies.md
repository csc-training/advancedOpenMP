---
title:  Task dependencies
author: CSC Training
date:   2024
lang:   en
---

# Task dependencies {.section}

# Tasks Synchronization: **taskwait**

<div class="column">
```c
  #pragma omp parallel
  #pragma omp single
  {
    #pragma omp task 
    modify_data(X) // Task A
    #pragma omp task 
    modify_data(Y) // Task B

    #pragma omp taskwait //The execution pauses here

    #pragma omp task 
    print_results(X) // Task C

    #pragma omp task 
    print_results(Y) // Task D
}
```
</div>
<div class="column">
```fortran
  !$omp parallel
  !$omp single
    !$omp task 
        modify_data(X) ! Task A
    !$omp end task
    !$omp task 
        modify_data(Y) ! Task B
    !$omp end task
    !$omp taskwait ! The execution pauses here
    !$omp task 
        print_results(X) ! Task C
    !$omp end task
    !$omp task 
        print_results(Y) // Task D
    !$omp end task
    ...
```
</div>

# Tasks dependencies

<div class="column">
```c
  #pragma omp parallel
  #pragma omp single
  {
    #pragma omp task depend(out:X)
    modify_data(X) // Task A
    #pragma omp task depend(out:Y)
    modify_data(Y) // Task B

    #pragma omp task depend(in:X)
    print_results(X) // Task C

    #pragma omp task depend(in:Y)
    print_results(Y) // Task D
}
```
</div>
<div class="column">
```fortran
  !$omp parallel
  !$omp single
    !$omp task depend(out:X)
        modify_data(X) ! Task A
    !$omp end task
    !$omp task depend(out:Y)
        modify_data(Y) ! Task B
    !$omp end task

    !$omp task depend(in:X)
        print_results(X) ! Task C
    !$omp end task
    !$omp task depend(in:Y)
        print_results(Y) // Task D
    !$omp end task
    ...
```
</div>

# Tasks dependencies Continued
 - Three types of dependencies: *in*, *inout*, *out*

```c
  #pragma omp parallel
  #pragma omp single
  {
    for(int i=0;i<5; i++){
      #pragma omp task depend(in: data) // in: depend on all previous out/inout tasks
        printf("task A %d\n", i);sleep(1);

      #pragma omp task depend(inout: data) // inout: depend on all previous in/inout/out tasks
        printf("task B %d\n", i);
    }
    #pragma omp task depend(out: data) // out: depend on all previous in/inout/out tasks (same as out)
    {
      printf("task C\n");
    }
  }
  ``` 
# Summary

- OpenMP tasks
