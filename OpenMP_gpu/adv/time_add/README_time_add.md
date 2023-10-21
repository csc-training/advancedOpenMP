# Time Offload kernel for vector add, and data motion

## Background

By putting timers around the "target data" directive"
and immediately after the target data region begind,,
the "target" construct, and the termination of the target
data region, one can measure the time required to 

```
   (allocate device data and) move data "to" the device, 

   execute and kernel, 

   and move data "from" the device (and deallocate).
```

## Exercise
    STATUS:  Makefile works for CPP only at this time.

1.) Add the start and stop timers around the appropriate
    areas, and run with the default (present) "target"
    construct to offload the add function.  Make sue it works.
    See previous examples (basic/worksharing) for including a timer:
    TODO 1:
    Note, the data motions due to the target data
    construct are measured separately at the beginning and end
    of the target data region.
    
    TODO 2:  2a target ENCLOSING function, 2b constructs IN function
    Change 1<<25 to 1<<28 for C/C++; 2**25 to 2**28 for Fortran for timing.

    Note: For the "add" procedure, the target and the target teams can be
    hoisted outside the function.  The different forms are labeled with
    F1, F2, F3, and F4.  Experiment with (time) the differents forms,
    and determine which one works best with defaults, and then experiment
    with the number of teams and thread limit for the optimal version.
    Which one has the highest performance.

    TODO 3:
    Now try running the Loop version (which doesn't
    call the function) L1, L2, L3, with various different 
    "target" directives (number of teams and thread limit).

    Which one has the highest performance.
