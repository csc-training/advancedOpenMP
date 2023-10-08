#include  <stdio.h>
#include <unistd.h>
#include    <omp.h>
// TODO 1a: Include timer.hpp
#include "timer.hpp"
int main(){

// TODO 1a: Instantiate a Timer class as timer.
   Timer timer;

// TODO 1b: Time a 1 second sleep
   timer.start(" 1 sec sleep ");
   sleep(1);
   timer.stop();

// TODO 1c: Now time a print statement
   timer.start(" printf io   ");
   printf( " Hello Helsinki.\n");
   timer.stop();

// TODO 1d: report measurements
   timer.print();

}
