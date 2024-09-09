#include <iostream>
#include <omp.h>
using namespace std;
class Vec{
public:
  Vec(int n) : len(n){
     v = new double[len];
     // TODO 1:  insert a a target enter data construct here
  }
  ~Vec(){
     // TODO 2:  insert a a target exit data construct here
     delete[] v;
  }
//private:
   double  *v;
   int    len;
};

int main(){
  int n=16;
  Vec cl_v(n);
  for(int i=0; i<n; i++) cl_v.v[i]=1.0f;

  // TODO 3:  offload with a target construct (no clauses)
  for(int i=0; i<n; i++) cl_v.v[i]=11.0f;

  // TODO 4:  use an update construct to get back from device

  for(int i=0; i<n; i++) cout << i << " " << cl_v.v[i] << endl;
}

