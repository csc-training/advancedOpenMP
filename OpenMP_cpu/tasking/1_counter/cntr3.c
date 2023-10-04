#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(){

  int cntr=100;
  #pragma omp parallel
  #pragma omp single
  {
     int i=0;
     while(cntr>0){
       #pragma omp task // what clause goes here for cntr?
       {
          if( i  ==  50 ) { 
             system ("sleep 1");
             printf("Expecting %3d, value=%3d \n",i,cntr);
          }
       }
       cntr--;
       i++; 
     }
  }
}
