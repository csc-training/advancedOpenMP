#include <stdio.h>
#include <omp.h>
void load_cpu_nsec(int sec);
int main(){
double t0,t1;
  int work[24]={1,1,1,1,  1,1,1,1,  1,1,1,1,  7,6,1,1,  1,1,1,1,  1,1,1,1} ;
//int work[24]={1,1,1,1,  7,6,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1} ;

      t0=omp_get_wtime();
   #pragma omp parallel num_threads(4)
   #pragma omp single
   {
    //t0=omp_get_wtime();
      for(int i=0; i< 24; i++){
        #pragma omp task firstprivate(i)
        {
        //printf(" thread=%0.2d  work=%2d work_amount=%2d\n", omp_get_thread_num(),i, work[i]);
          load_cpu_nsec(work[i]);
        }
      }
   }
      t1=omp_get_wtime();
   printf("execution time %f \n",t1-t0);

}
