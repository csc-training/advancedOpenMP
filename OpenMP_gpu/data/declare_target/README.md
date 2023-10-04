# delcare target directive for out-of-scope functions and variables

  1.) Look over main.cpp and fun.cpp

      main calls the procedure (function) in a target region
      and fun() is in another compilation scope.
      Also, fun() uses the global (static) "a" variable.

      The Makefile compiles them separately,
      and then loads them to make an a.out executable.

  2.) Compile and run the code, as is, wo openmp,
      to make sure it works.
      (Don't forget to execute "make clean".)

  3.) Now turn on openMP offloading in the makefile
       a.) uncomment the OMP_FLAG and OMP_TARG 
           assignments to turn on OpenMP, and OpenMP offloading.

       b.) Add efficient mapping clause (tofrom for y and to for x)

           (Don't forget to execute "make clean".)
       c.) Compile and run.
           What happened in the compilation. Hmmm undefined symbo: "fun".
           The compiler is looking for a device version of the 
           fun function. (Implicitly it knows there should be one
           and if were defined in this scope, it would have made
           a gpu version.  But fun was compiled separately, by
           default as host-only function.
  4.) 
       a.) Add a declare target directive for the fun function and
           global variable in fun.cpp.  The simplest way is with a
           by enclosing these object with a begin declare target
           and an end declare target directive.
       b.) compile and run.

   5.) How else could you have used declare target?
