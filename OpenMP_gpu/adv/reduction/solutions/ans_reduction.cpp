#include <stdio.h>
#include <omp.h>

float dotprod(float B[], float C[], int n)
{
   float sum       = 0.0f;
   int   sum_teams = 0;
   int   got_teams = 0;

// TODO 1a: map B and C and scalars as "tofrom"
// TODO 1b-c include reductions for sum and sum_teams.
   #pragma omp target teams num_teams(100) \
                            map(to: B[0:n], C[0:n]) defaultmap(tofrom:scalar) \
                            reduction(+:sum,sum_teams)
   {      //TODO 1b
      #pragma omp distribute parallel for reduction(+:sum)
      for (int i=0; i<n; i++) sum += B[i] * C[i];

      sum_teams+=1;
      if(omp_get_team_num()==0) got_teams=omp_get_num_teams();
   }

   printf("sum_teams = %d, got_teams = %d, sum = %f (n = %d)\n",sum_teams,got_teams,sum,n);
   return sum;
}

int main(){
   int  N=1<<20;
   float sum, B[N],C[N]; //init vv
   for(int i=0; i<N; i++){B[i]=1.0f; C[i]=1.0f;}

   sum=dotprod(B,C,N);
}
// Without defaultmap
// #pragma omp target teams num_teams(100) \
//                          map(to: B[0:n], C[0:n]) map(tofrom:got_teams) \
//                          reduction(+:sum,sum_teams)
