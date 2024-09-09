
// TODO 2: include timer.hpp here

int main(void)
{
  int     N = 1<<29;
  float x[N], y[N], a=2.0f; 

// TODO 2: Instantiate timer object here 


  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++) { x[ i] = 1.0f; y[ i] = 1.0f; }

  // TODO 2: Start timer here, around target construct

  // TODO 1: Offload with teams distribute parallel for

  { for (int i = 0; i < N; i++) y[i] = a*x[i] + y[i]; }

  // TODO 2: Stop timer here and report resuls

  return 0;
}

