# Setting task priority with the priority hint.

1.) priory is a hint, and may not be implemented for
    the compiler used at the site.

    Suggestion: know the concept, look at the code,
    but don't expect it to work (don't try to make it
    work). You might look at the timers.c code to 
    check out different timers.

    !THIS IS WORK INPROGRESS!

    Look over the priority code (priority.c).
    The work array has 24 elements, each indicating the # of units of work to be done.
    There are two arrays.  One (1) has some large work arrays in the middle. 
                           The other (2) has the same large work arrays in near the beginning

    24 tasks are generated to do the work.

    Compile and run using work array 1 (default).
    Comment out work array 1 and uncomment out work array 2, to use it.
    Compile and run using work array 2.

    Compilation:
```
      CC -D _GNU_SOURCE load.c timers.c -c
      CC -fopenmp priority.c load.o timers.o
```
    What is the time for work arrays 1 and 2   (1) ______    (2)________

    So, it appears that scheduling the large amounts of work ealier leads
    to better balancing (among 4 threads) and faster execution.


    What clause would you use on the task to assure that the larger work requests
    are scheduled first. ______________

    Write out the clause and "argument" you would use.__________________

    
