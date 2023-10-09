// TODO 1
#include <sstream>
#include <iostream>
#include <omp.h>
using namespace std;

int main(){
 #pragma omp parallel num_threads(64)
 {
   int t = omp_get_thread_num();
   int s = t+1;
   // TODO 2:  Create a single string for cout to print s and t
   //          as " # from thread no #"
   stringstream onestring;
   onestring << s << " from thread no " << t << endl;
   cout << onestring.str();
 }
}
