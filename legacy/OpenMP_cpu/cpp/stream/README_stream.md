# Using class methods with dynamic scope (with worksharing)

## BACKGROUND
With parallel threads the cout "arguments" are written as a stream
to stdout, and the printed variables will not be printed as a single
group, the interdispersed among the other cout outputs.

## Exercises
1.)
    Look over the code.
    Compile and runt (with -fopenmp).
    Note that output is not readable.

2.) Include the header for sstream, //TODO 1:
    create a  stringstream type variable, and
    write the content used by the present cout
    to the variable, and then print the variable. //TODO 2.

    Compile (debug) and run.
