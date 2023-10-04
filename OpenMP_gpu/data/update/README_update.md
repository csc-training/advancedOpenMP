# target update construct target data construct

The target update makes the original and 
corresponding data consistent by copying
date "to" or "from" device. 

Either the "to" or "from" data motion clause
is required, and multiple ones can exist with
different variables (items).
The "if" clause can be used for conditional updates.
A device can be selected with the device clause
(In addition, see later examples, async behavior
 with nowait and depend claused can be invoked.)


Compile and run `update(.cpp|.F90)` 

1.) Look over the code.  
    Compile and run `update(.cpp|.F90)`, as is,
    with offloading support to make sure it is
    working right.

2.) Create a structured data region enclosing the 
    two target offload constructs,
    mapping v1 and v2 with "to", and p with "from".
    Conditionally update v1[0] (C/C++) or v1(1)
    (F90) after calling the maybe_change_v1 routine
    is called

Note: _OPENM _OPENMP= 201811 for present LUMI compiler.
Note: for C/C++: if clause is false for "0", otherwise true
Note: for F    : if clause is true for .TRUE., and false for .FALSE.   

```
./a.out
```

