# array section in map clause



Change the arrays X and Y arrays to dynamic arrays
and map the pointer and the pointee storage with 
array sections
Compile and run `array_section(.cpp|.F90)` 

1.) Look over the code.  
    Array X and Y are mapped implicitly in the target region.
    (You can compile and run the codes, as is; it will work.)
    Allocate X and Y as dynamic arrays (do nothing more). TODO 1:

    Compile the code and run, as is, with one thread on target
       Why doesn't implicit mapping work here?
       Did you get a message:
       Hint: with Cray clang++ message is: 
        Memory access fault by GPU node-4 ...

   2.) Fix it by including an explicit map clause
       with an array section which maps the pointer and 
       the data pointed to. TODO 2:
       (hint:  array section format: map(ptr[<start>:<#of elements>])
       Compile and run.

       If you didn't use a map-type (to|from|tofrom)
       to minimize transfers, do that, and run again.

   3.) Now, only map elments n/2 to n-1, and
       perform the axpy on the mapped elements. 
       (Also fix the assert.)

   4.) Try setting a stride and compiling. 
       Does it work on this versions of the compiler?

```
./a.out
```
