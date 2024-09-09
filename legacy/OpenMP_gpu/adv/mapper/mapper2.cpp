#define N  100 
#include <iostream>
using namespace std;

typedef struct v_t 
{  int len;
   double *a;
} v_t;

 // TODO 2a:
 // create mapper with lef_id identifier, for strucutre type v_t
 // with a map of array section a[0:N/2]
#pragma omp declare mapper( left_id: v_t v) \
                       map( v, v.a[0:N/2] )

int main(){
   v_t my_vec;

   // TODO 2a: map my_vec, using the identifier left_id
   // with map type of tofrom
   #pragma target map(mapper(left_id),tofrom: my_vec)
   for(int j=0; j<N/2; j++) my_vec.a[j] = 9;

   cout << "my_vec.a[0] = " << my_vec.a[0] << endl;
}
