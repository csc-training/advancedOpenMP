program main  !unverified
  integer, parameter :: n=16
  integer :: a=2, version=0
  integer :: x(n), y(n)

  !! TODO 1c:  create a data region up to TODO end 1c
  !!           with minimum data motion


     !! TODO 1a: offload without any mapping

        do i=1,n; x(i)=1; y(i)=1; enddo

  
     !! TODO 1b: offload without any mapping

        do i=1,n; y(i)=a*x(i)+y(i); enddo


   !! TODO end 1c:


   do i=1,n; if(y(i) /= 3) stop("y != 3"); enddo

   print*, "Passed OpenMP ", _OPENMP

end program
