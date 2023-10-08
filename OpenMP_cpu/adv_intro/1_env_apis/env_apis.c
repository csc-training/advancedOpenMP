#include <stdio.h>
#include <omp.h>

int main(){

// TODO 3: display the "ENV" and affinity
   // omp_display_<TODO>;
   // omp_display_<TODO>;
   //omp_display_env(1);
   //omp_display_affinity(NULL);
// omp_display_se

// TODO 1: get the thread number and number of threads
   #pragma omp parallel
   {   
    // printf( " %d out of %d\n", omp_get_<TODO>, omp_get_<TODO> );
      printf( " %d out of %d\n", omp_get_thread_num(), omp_get_num_threads() );
   }   

}
