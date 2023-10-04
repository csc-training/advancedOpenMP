program main   !unverified
  integer, parameter :: n=16
  integer :: a=2, version=0
  integer :: x(n), y(n)

  !! TODO 1c:  create a data region up to TODO end 1c
  !!           with minimum data motion
   !omp target data map(alloc: x) map(from: y)

     !! TODO 1a: offload without any mapping
     !omp target
        do i=1,n; x(i)=1; y(i)=1; enddo
     !omp end target
  
     !! TODO 1b: offload without any mapping
     !omp target
        do i=1,n; y(i)=a*x(i)+y(i); enddo
     !omp end target

   !! TODO end 1c:
   !omp end target data

   do i=1,n; if(y(i) /= 3) stop("y != 3"); enddo

   print*, "Passed OpenMP ", _OPENMP

end program
