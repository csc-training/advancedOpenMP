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
#pragma omp single
   while(...){           //<-- do while: ??? is not null
      #pragma ...        //<-- execute foo as a task
      foo(...);          //<-- function to task, hand it the pointer

                         //    single threaded
      ... = ...->next;   //<-- advance the pointer

   }
}

void foo(struct node *ptr){      // do work here
   printf(" executed node %0.3d  thread %0.2d \n",ptr->x,omp_get_thread_num());
}
