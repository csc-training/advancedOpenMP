program main
  integer, parameter :: n=16
  integer :: a=2, version=0
  integer :: x(n), y(n)

!! TODO 1:  Give x and y allocatable attributes
!!          and allocate them dynamically

   do i=1,n; x(i)=1; y(i)=1; enddo  !! init

   !! one thread executes the loop
   !! TODO 1: no map required for allocatable arrays
   !! TODO 2: Use array sections for last 1/2 of array
   do i=1,n; y(i)=a*x(i)+y(i); enddo


   do i=1,n; if(y(i) /= 3) stop("y != 3"); enddo

#ifdef _OPENMP
   print*, "Passed OpenMP ", _OPENMP
#else
   print*, "Passed OpenMP off"
#endif

   !! TODO 2:  Do axpy on last have of vectors
   !!          Modify map, axpy loop and validate loop
end program
