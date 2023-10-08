#include <stdio.h>
#include <omp.h>

int main(){

// TODO 3: display the "ENV" and affinity
     omp_display_env(1);         // does not work on Lumi cce 15.0
     omp_display_affinity(NULL);

// TODO 1: get the thread number and number of threads
   #pragma omp parallel
   {   
      printf( " %d out of %d\n", omp_get_thread_num(), omp_get_num_threads() );
   }   

}
