#include <stdio.h>
int main(){
   int a[2]={9,9};

   // TODO 1a:  map the data tofrom (same as implicit)
   // TODO 1b:  map the data from   (optimal)
   // TODO 1c:  map the data to     (not what you want)
   // TODO 4:  specify defaultmap(none)  only
   // TODO 5:  specify defaultmap(from:aggregate) only

// #pragma omp target defaultmap(none)
// #pragma omp target defaultmap(from:aggregate)
   #pragma omp target map(from:a) // or  map(to: a) or  map(tofrom: a)
   { a[0]=0; a[1]=1;}

   printf("%d %d\n",a[0], a[1]);
}
