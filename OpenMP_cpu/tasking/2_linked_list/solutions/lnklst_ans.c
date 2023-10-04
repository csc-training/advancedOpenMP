#include <stdio.h>
#include   <omp.h>
#define N 100

struct node {
  int x;
  struct node *next;
};

void foo(struct node *ptr);

int main(){
int i;
struct node *ptr;

//   Trivially create nodes via
//   an array of nodes, link them.
struct node a[N];
   for(i=0;i<N-1;i++){
      a[i].x= i;
      a[i].next=&a[i+1];
   }
   a[N-1].x   =N-1 ;
   a[N-1].next=NULL;
   

   ptr=&a[0];

#pragma omp parallel
#pragma omp single firstprivate(ptr)
   while(ptr){           //<-- do while ??? is not null
      #pragma omp task   //<-- execute foo as a task
      foo(ptr);          // function to task hand it the pointer

      ptr = ptr->next;   // advance the pointer

   }
}

void foo(struct node *ptr){      // do work here
   printf("thread %0.2d executed node %0.3d\n",omp_get_thread_num(),ptr->x); 
}
