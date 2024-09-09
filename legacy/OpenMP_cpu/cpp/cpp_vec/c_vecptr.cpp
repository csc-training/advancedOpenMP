#include <iostream>
#include <omp.h>
using namespace std;
#define Nthreads 16
int main() {

  int *array = (int*) malloc(Nthreads*sizeof(int));

  for (int i=0; i<Nthreads; i++) array[i] = 0;

  #pragma omp parallel firstprivate(array) num_threads(Nthreads)
  {
    int t = omp_get_thread_num();
    array += t;
    array[0] = t;
  }

  for (int i=0; i<Nthreads; i++) cout << i<< " "<<array[i]<<endl;

}
/*

    Here an array pointer is incremented to a position equal to
    the thread number (0, 1, 2, 3), and then the thread number is
    inserted.  The point (no pun intended) here is that array
    variable is privatized and assigned its initial value 
    to be used by each thread (thereby
    avoiding nonsense and race condition assignments).

    Can you do this for an array? (if you replaced malloc statement
    with "int array[Nthreads];".  No, because even though array could
    be used as if it is a pointer, array is not a modifiable lvalue.

    Wouldn't it be much easier just to use:
       array[omp_get_thread_num()]=omp_get_thread_num();
    
    
*/

/*  output
Ft2 vector_copy $ a.out
0 0
1 1
2 2
3 3
*/
