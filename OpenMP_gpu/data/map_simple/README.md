# map 1 simple map clauses



Use the map clause to evaluate the effects of "tofrom", "to" and "from" map types.
Compile and run `map1(.cpp|.F90)` for each case.

1.) Look over the code.  It assigns values to the "a" array.
    Map the "a" array for each map type.
    Compile and run each time you change the map, and make sure
    the results are as you would expect. TODO 1a-c:
    (That is the default mapping?)

2.) Remove any map clause, and include the defaultmap(none) clause
    This is like "implicit none" in the Fortan language. TODO 2:
    Compile:
    What did the compiler state? 

    After the defaultmap(none) include map(from:a)
    Compile and run.

3.) Now, just use the defaultmap clause to set ALL
    (OpenMP) aggregate types (an OpenMP variable-category)
    to an implicit behavior of "from" map type. TODO 3:


     Hint: defaultmap(map type: variable-category) 

     You can always override the default map by
     including a map for specific variables:
     defaultmap(to:aggregate) map(from:a) 
     will override the default for a.


```
./a.out
```
