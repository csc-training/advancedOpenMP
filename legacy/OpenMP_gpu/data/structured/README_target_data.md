# structured data region with target data construct

The target data construct is used to
perform data motion at the beginning and end 
of a (it's) blocked region.

If it encloses multiple target constructs (regions),
mapping is precuded from occuring for the offloading
target constructs.  (It handles this by 
"reference counting", more on this later.)

This is idea way map once for a set of offload.

Create a structured data region for two offload.
Compile and run `structured(.cpp|.F90)` 

1.) Look over the code.  
    Offload each of the (two) loops
    loops separately, without any
    explicit mapping.  In this case
    implicit tofrom mapping occurs for
    each target region.  TODO 1a-b.

    Now enclose both target constructs  with a
    target data region.
    Include maps that are optimal about moving
    or not moving data.

    Hint: 
      Is there any day motion required for x?
      Is it necessary to move y data to the device?

```
./a.out
```

