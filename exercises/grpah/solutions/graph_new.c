#include <stdio.h>
void f1(int *a, int *b, int *c);
void f2(int *d, int *e);
void f3(int c, int d);
void f4(int *e);
void f5(int a, int *b, int *c, int e);

int main(){
int a,b,c,d,e;

   #pragma omp parallel
   #pragma omp single
   {
     #pragma omp task depend(out:a,b,c)             //TASK 1
       f1(&a, &b, &c);
     #pragma omp task depend(out:d,e)               //TASK 2
       f2(&d, &e);
     #pragma omp task depend(in:c,d)                //TASK 3
       f3(c,d);
     #pragma omp task depend(inout:e)                 //TASK 4
       f4(&e); 
     #pragma omp task depend(in:a,e) depend(out:b,c)  //TASK 5
       f5(a,&b,&c,e);
   
   }
   printf("\nEND: a,b,c,d,e = %1d %1d %1d %1d %1d\n",a,b,c,d,e);
}
   
void f1(int *a, int *b, int *c){
            *a = 1; *b=1;   *c=1;
            printf("T1  OUT_dep  a,b,c %1d,%1d,%1d\n",*a,*b,*c); 
}
void f2(int *d, int *e){
            *d = 1; *e=1;
            printf("T2  OUT_dep  d,e %1d,%1d\n",*d,*e); 
}
void f3(int c, int d){
        if(c !=d) printf("Hmm\n");
        printf("T3   IN_dep  c,d %1d,%1d\n",c,d);
}
void f4(int *e){
        *e+=5;
        printf("T4   INOUT_dep  e %1d\n",*e);
}
void f5(int a, int *b, int *c, int e){
        if(a==0) printf("Hmm\n"); 
        *b=9; *c=9;
        printf("T5   IN_dep  a,e =%1d %1d    OUT_dep b,c %1d %1d\n",a,e,*b,*c);
}
