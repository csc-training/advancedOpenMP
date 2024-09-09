#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(){

 int cntr=100;
 printf(" The sequence of values printed should be, 1 - 100.\n");
 printf(" Execute:  ./a.out | sort for checking.\n");

 #pragma omp parallel
 #pragma omp single

  while(cntr>0){
    #pragma omp task  // <--what clause goes here for cntr?
    {
       if( omp_get_thread_num() == 0 ) system ("sleep 1");
       printf(" cntr value=%0.4d   thrd: %0.3d\n", cntr, omp_get_thread_num());
    }

    cntr--;
  }

}
