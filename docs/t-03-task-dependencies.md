---
title:  Task dependencies
author: CSC Training
date:   2024
lang:   en
---

# Task dependencies {.section}

# Tasks Synchronization (**taskwait**) and Dependencies

<div class="column">

- Some situations require tighter control on synchronizations.
- How to **task**ify correctly?
    - Where to insert **taskwait**?

</div>

<div class="column">
```c
{
  a=foo_a();
  b=foo_b();
  c=foo_c();
  d=foo_add(a,b);
  e=foo_mul(d,c);
}
``` 
</div>

# Tasks Synchronization: **taskwait**


<div class="column">
```c
{
  a=foo_a();
  b=foo_b();
  c=foo_c();
  d=foo_add(a,b);
  e=foo_mul(d,c);
}
``` 
</div>

<div class="column">
![](img/DAG1dep.png){.center width=61%}
</div>


# Tasks Synchronization: **taskwait**


<div class="column">
```c
{
  #pragma omp task
  a=foo_a();
  #pragma omp task
  b=foo_b();
  #pragma omp task
  c=foo_c();

  #pragma omp taskwait
  #pragma omp task
  d=foo_add(a,b);

  #pragma omp taskwait
  #pragma omp task
  e=foo_mul(d,c);
}
```  
</div>

<div class="column">
![](img/DAG2dep.png){.center width=61%}
</div>



# Tasks Synchronization: taskwait

<div class="column">
```c
{
  #pragma omp task
  a=foo_a();
  #pragma omp task
  b=foo_b();

  #pragma omp taskwait
  #pragma omp task
  c=foo_c();
  #pragma omp task
  d=foo_add(a,b);

  #pragma omp taskwait
  #pragma omp task
  e=foo_mul(d,c);
}
``` 
</div>

<div class="column">
![](img/DAG3dep.png){.center width=61%}
</div>

# Tasks dependencies

```c
{
  #pragma omp task depend(out:a)
  a=foo_a();
  #pragma omp task depend(out:b)
  b=foo_b();
  #pragma omp task depend(out:c)
  c=foo_c();

  #pragma omp task depend(in:a,b) depend(out:d)
  d=foo_add(a,b);
  
  #pragma omp task depend(in:c,d)
  e=foo_mul(d,c);
}
```  


# Tasks dependencies types

 - Three types of dependencies: **in**, **inout**, **out**
  - **depend(in:x)**: task will read the variables **x**.
  - **depend(out:y)**: task will write the variable **y**.
  - **depend(inout:z)**: the task will both read and write the variable **z**.

# Tasks dependencies mutexinoutset

 - The option **mutexinoutset** ensures that tasks accessing the same memory locations are executed in a mutually exclusive manner.


```c
 #pragma omp task depend(out: res) 
 res = 0;
 #pragma omp task depend(out: x) 
 long_computation(x);

 #pragma omp task depend(out: y) 
 short_computation(y);
 #pragma omp task depend(in: x) depend(mutexinoutset: res) 
 res += x;
 #pragma omp task depend(in: y) depend(mutexinoutset: res) 
 res += y;

 #pragma omp task depend(in: res) 
  printf("%d \n", res);
``` 

# Tasks dependencies depobj

 - Dependencies between tasks can be put into object  which can be modified during the runtime using **depobj**.
    - Useful for complex task dependences. 
    - It allows a more efficient allocation of task dependences

```c
 omp_depend_t obj;
 #pragma omp depobj(obj) depend(inout: x)
 #pragma omp task depend(depobj: obj) 
  x++;

 #pragma omp depobj(obj) update(in)
 
 #pragma omp task depend(depobj: obj) 
  printf("%d \n", x);
 #pragma omp depobj(obj) destroy
``` 

# Task dependencies taskwait

 - The **depend** clause can be used with **taskwait** as well. 
    - The execution pauses until the dependencies are satisfied.

```c
#pragma omp task depend(inout: x) 
 x++;

 #pragma omp task depend(in: y) 
 printf("%d \n", y);

 #pragma omp taskwait depend(in: x)
 printf("%d \n", x);
``` 

# Summary

- The **depend** clause gives information about the way a task will acess the data
- Access mode can be **in**, **out**, and **inout**.
- Set tasks that can not be executed simultaneous **mutexinoutset**.
- It is posible to specify deoendencies via an object using **depobj**.
- The **taskwait** construct can have as well dependencies.
- The execution of the task is decided by the OpenMP runtime dynamically, based on its dependencies. 
