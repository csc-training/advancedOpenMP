# target enter|exit data constructs for unstructured data motion

You can use target enter data map()
and         target exitr data map()
anyplace. In particular they are useful when
routine are used to create/free data.

In the unstructured(.c | .cpp | .F90) program
initial and free routines are used with
with struct, class and allocatable types
for creating data and freeing it.

Within the initialization and freeing routine
add OpenMP pragmas target enter/free data
constructs to create device space (alloc)
and free (delete) device space (in conjunction
with the host operations).

Work on one the the code: `unstructured(.c | .cpp | .F90)` 

1.) Look over the code.  
    In the C++ class Vec(), ~Vec()
       or  C   init_A(), free_A
       or  F   init_A(), free_A() 

    add a "target enter data" construct AFTER
    allocating space for the data.    TODO 1:

    add a "target exit data" construct BEFORE
    deallocating space for the data.  TODO 2:

    Offload the assignment loop in main with
    just a target construct (no clauses). TODO 3:

    use an target update construct after the
    offload target construct to get the device
    data back. TODO 4:

    Compile, run and verify results.

```
./a.out
```

