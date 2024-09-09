#include "omp.h"
#include <stdio.h>
void foo(int);

int main(){

   #pragma omp parallel
   {
     foo(omp_get_thread_num());
   }
}

void foo(int id){
  printf("thrd_id %0.3d\n",id);
}
