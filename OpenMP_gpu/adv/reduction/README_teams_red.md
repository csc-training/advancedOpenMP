# reductions in target teams regions (teams reduction)

Since teams are different contention groups,
reductions across the teams is accomplished 
with a reduction clause.  Effectively, reduction
across the teams works the same was as
a reduction across the loop.

If there is a parallel for|do in a target region
which performs a reduction, include a 
reduction clause (of course).  For a combined
```
    target teams disbribute parallel for|do
```
it is only necessary to include a reduction clause.
However, if the distribute parallel for|do is a
nested construct of a target teams, then it is
necessary to include a reduction across the teams
(contention groups) and the parallel work-sharing:
```
    target teams  ...  reduction(<op1>,var1)
    ...
    disbribute parallel for|do reduction(<op1>,var1)
       for|do   var1=var1<op1>var
```

The reduction(.cpp | .F90) code illustrate the
latter situation with the separate "target teams" 
and distribute parallel for|do constructs.

1.) Look over the code.

    On the target teams construct 

     a.) map B and C as array sections with a 
         map type of "to". Just for fun, map all scalar
         variables as "tofrom" with the defaultmap clause.TODO 1a

     b.) Include a reduction clause on the target... and distribute...
         constructs. TODO 1b 

     c.) Also, there is a reduction on sum_teams in the 
         target teams region (only),
         include a reduction clause for it. The latter just check
         if the compiler adheres to upper bound of the num_teams(100)
         clause. Don't forget to map got_teams as "tofrom". TODO 1c

     d.) Compile and run with OpenMP offloading.
         Did you get the correct result?

2.) Questions    
    Note, that the default(tofrom: scalar) will also
    map the sum as tofrom, as well as got_teams.

    Fortran:
    (Assume you set "i" to -1 before the target teams construct.)
    What will be the values of i after offload?  
    If you answered "the same as before offload", you are correct.
    (i is privatized for the loop indexing with the parallel for|do.)
   
    Is it necessary to include the defaultmap or explicitly map 
    sum and sum_teams as "tofrom"?  Try removing the defaultmap clause
    and just map got_teams as "tofrom".  Did it work? Why/Why no?

```
./a.out
