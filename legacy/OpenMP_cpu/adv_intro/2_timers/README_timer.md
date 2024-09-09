# Class Timer_Collector  -- collects time measurements and reports them later.

## BACKGROUND
Fortran and CPP Timer classes have been created for measuring performance
of code blocks demarked by start() and stop() class member functions.
For each block a literal character string argument for start("my label")
is used as a label when the times are reported with print().
```
      Declare Timer_collector as timer
               CPP                                F90
      timer.start("my label")             call timer%start("my label")
      <something to be timed>             <something to be timed> 
      timer.stop()                        call timer%stop()
      ...                                 ...
      timer.print()                       call timer%print()

      See timer.hpp (CPP) and timer.f90 (F90)

```
## Exercises

1.) 
    Look over time_print(.cpp|.f90).  The TODOs guide you
    through instrumenting the code for timing 

    a sleep routine, and

    -- That is just to make sure the timer is working.---

    a write to stdout (CPP: printf, F90: print*,)
    
    TODO 1:
    Include the Timer_collector class file (CPP: timer.hpp, F90: timer.f90)
    at the beginning of the code.

    TODO 2:
    Instantiate the class in main as timer:
    CPP:  Just use "Timer_Collector timer;"
    F90:  Use the module defined in timer.f90 (mod_timer)
          and define "timer" as type(Timer_Collector).

    TODO 3:
    Time the sleep and print statements:
    CPP: Put      time.start("my label") and      time.stop() before and after
    F90: Put call time%start("my label") and call time%stop() before and after

    TODO 4:
    Report the times at the end.

    Is the timer reporting reasonable numbers?
    What are the units?
    How accurate is the timer?
    How long did the print statement take?
    (Note, the print time is just to write to an io buffer.)
    How much time is use in calling the timer?
    How would you measure that?
