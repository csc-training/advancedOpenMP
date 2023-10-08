# Class Timer  -- collects time measurements and reports them later.

## BACKGROUND
Fortran and CPP Timer classes have been created for measuring performance
of code blocks demarked by start() and stop() class member functions.
For each block a literal character string argument for start("my label")
is used as a label when the times are reported with print().

See timer.hpp (CPP) and timer.f90 (F90)

## Exercises

1.) 
    Look over time_print(.cpp|.f90).  The todo's guide you
    through instrumenting the code for timing 

    a sleep routine, and

    -- That's just to make sure the timer is working.---

    a write to stdout (CPP: printf, F90: print*,)
    
    TODO 1:
    Include the Timer class file (CPP: timer.hpp, F90: timer.f90)
    at the beginning of the code.

    TODO 2:
    Instantiate the class in main as timer:
    CPP:  Just use "Timer time;"
    F90:  Use the module defined in timer.f90 (mod_timer)
          and define timer as type(cls_timer).

    TODO 3:
    Time the sleep and print statements:
    Put      time.start("<label>") and      time.stop() before and after
    Put call time%start("<label>") and call time%stop() before and after

    TODO 4:
    Report the times at the end.

    Is the timer reporting reasonable numbers?
    What are the units?
    How long did the print statement take?
    What is the resolution of the timer.
    How much time is use in calling the timer?
    How would you measure that?
    (TODO, fortran needs to report more digits)
