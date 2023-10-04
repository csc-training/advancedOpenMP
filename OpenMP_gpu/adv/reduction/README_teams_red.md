# reductions in target teams regions (teams reduction)

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

    On the target teams construct 

     a.) map B and C as array sections with a 
         map type of to. TODO 1a

     b.) For giggles, use a defaultmap clause
         to map all scalars as to from (for the
         sum variable). TODO 1b

     c.) Note, the reduction for the parallel for|do
         in the next directive.  If necessary,
         also include this reduction clause on
         the target teams construct. TODO 1c

     d.) Compile and run with OpenMP offloading.
         Did you get the correct result?

2.) Questions    
    Note, that the default(tofrom: scalar) will also
    map the sum as tofrom, as well as N and i.  
    (Assume you set "i" to -1 before the target teams construct.)
    What will be the values of N and i after offload?  
    If you answered "the same as before offload", you are correct.
    (i is privatized for the loop indexing with the parallel for|do.
     N is not reassigned.)
   
    Would it have been better to not use the default clause,
    (thereby allowing N and i to be firstprivate), and map sum as tofrom?
    Yes. Binary creation is slighly simpler, and overhead of
    transporting and keeping track of mapped objects is slight
    less.

```
./a.out
