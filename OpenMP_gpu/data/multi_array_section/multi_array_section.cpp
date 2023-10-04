#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
int a=2, n=1<<4; // 16
  int x[n], y[n];
  for(int i=0;i<n;i++){ y[i]=1; }

  // TODO 1:  map all of y as tofrom, and only approriately needed section of x
     for(int i=0  ;i<n/4;i++) x[i]=1;
     for(int i=n/2;i<n;  i++) x[i]=1;
     for(int i=0  ;i<n/4;i++) y[i]=a*x[i]+y[i];
     for(int i=n/2;i<n;  i++) y[i]=a*x[i]+y[i];


  for(int i=n/2; i<n;   i++) assert(y[i]==3);//Validate
  for(int i=0  ; i<n/4; i++) assert(y[i]==3);//Validate

    printf("Passed OpenMP %d\n", _OPENMP);
}

