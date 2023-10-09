// TODO 2: sstream header
#include <iostream>
#include <omp.h>
using namespace std;

int main(){
// TODO 1: Change the following code so that
//         cout uses one string of type stringstream
//         as defined by the  sstream header
//         string format:  " # from thread no #". 

 #pragma omp parallel num_threads(64)
 cout << omp_get_thread_num() << " out of " << omp_get_num_threads()<< endl;
}
