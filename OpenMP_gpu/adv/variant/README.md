# declare variant


Since teams are different contention groups,
reductions across the teams is accomplished 
with a reduction clause.  Effectively, reduction
across (FOR) the teams works the same was as
a reduction across (FOR) the loop.
If there is a parallel for|do in a target region
and teams is a component directive, also
include the reduction clause on the teams.

The reduction(.cpp | .F90) code illustrated this
concept with the separate "target teams" and
distribute parallel for|do constructs.

1.) Look over the code.

    Immediately before the definition of vxv (for C/C++)
    or at the end of the variable declartions (for F9)
    include 2 declare variant directives, one for
    p_vxv (parallel version) that matches a parallel construct,
    and another for t_vxv (target version) that matches
    a target construct.  TODO 1

2.) Add a begin declare target and end declare target
    around the definition of t_vxv for C/C++ codei
    (just in case the function definitions are 
    placed in another scope). TODO 2

    For Fortran code , insert a
    declare target directive at the end of the
    specification part of t_vxv().

3.) Questions    
     What is the pupose of the prototypes before the C/C++ OpenMP
     declare variants for the C/C++ code.?
     
     is the declare target even needed for the Fortran code
     (for a used module)? 

     How else could the declare target and declare variants
     be specified for the Fortran code?
```
./a.out
