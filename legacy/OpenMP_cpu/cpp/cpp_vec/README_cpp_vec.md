++ vectors in worksharing constructs

## BACKGROUND

## Exercise
1.) 
    Look over the code.
    Compile and run.
    Why do the two parallel region give different result?

    To somebody new to C++ (from the C world), one
    might be inclined to think that a vector variable 
    can be used as a pointer (as in c_ptrvec.cpp), but 
    that will not work. You would think the compiler 
    would warn you (as when you tried using an array
    in c_ptrvec.cpp), but it lets you shoot yourself in the foot.
    In the above parallel directive a copy of vector object
    is made and any updates are private to the thread.
    Hence, the first printing just returns the original "9" 
    values assigned to the vector.  The second printing
    does not privatize the vector.

2.) (Optional, for advanced users)
    If you want to do pointer manipulation, as in c_ptrvec.cpp,
    you could obtain a pointer to the first element of
    array, like this:
```
       int *array_ptr =array.data();
```
    We will discuss this trick in a later example.
