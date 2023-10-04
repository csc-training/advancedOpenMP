# Parallel Work with OpenMP offloading



The target teams distribute parallel for (ttdpf) construct 
(what a combined directive) parallelizes a for/do loop across 
teams for threaded execution using a default number of teams and threads.
   o First approach is to just let the compiler decide the
     best combination of thread per team and the number of teams.

1.) Insert the TTDPF directive to offload the axpy operation.
    Fortran folks, just use the cpp code.

    Compile and run to make sure it work.
    Did you need a header file?  Why not.


2.) Now instrument the file with the included timer.
    a.) insert the declaration:
           Timer timer;
    b.) around the TTDPF region, start, stop, and print
        the timer results:

           timer.start("    Offload     ");
           ...
        timer.stop();
        timer.print(); 

    c.) Compile and run.
        How much time did it take?
        Remember, moved data to the device (in a non optimal way)

    d.) Now increase the size of the problem by 4x:
      
        change 1<<29  to 1<<31

    e.) Compile and run
        Was the total cost 4x?
        Most of the was from data motion.
        We will look at that later.

```
Include the following code if youo want to check the results:

//Check for rounding errors

//Include following headers and namespace 
//statement at beginning
#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;

  //Insert after axpy calculation
  float maxerr = 0.1f;
  for (int i=0; i<N; i++)
  {
    maxerr = fmax(maxerr, fabs(y[i]-3.0f));
    assert(maxerr < 0.0000001); 
  }

```
