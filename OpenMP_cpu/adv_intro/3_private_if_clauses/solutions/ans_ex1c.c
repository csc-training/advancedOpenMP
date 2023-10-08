// ex1c.c
#include "omp.h"
#include <stdio.h>
void foo(int);

int main(){
   int id;

   #pragma omp parallel
   {
    if(omp_get_thread_num() > 0){
      id = omp_get_thread_num();
      system("sleep 1");
    }
    else{
      id = omp_get_thread_num();
    }
    foo(id);
   }
}

void foo(int id){
  printf("thrd_id %0.3d\n",id);
}
