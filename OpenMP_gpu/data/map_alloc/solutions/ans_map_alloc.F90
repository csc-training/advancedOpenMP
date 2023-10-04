program main

  integer, parameter :: n=16
  integer :: a=2, version=0

  integer :: x(n), y(n)

   do i=1,n; y(i)=1; enddo  !! init only y

   !! TODO 1: only allocate space for x on device
   !! reduced number of data transfers
   !$omp target map(alloc: x) map(tofrom: y)
      do i=1,n; x(i)=1;           enddo
      do i=1,n; y(i)=a*x(i)+y(i); enddo
   !$omp end target

   do i=1,n; if(y(i) /= 3) stop("y != 3"); enddo

   print*, "Passed " _OPENMP

end program
