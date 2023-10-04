program main
  integer, parameter :: n=16
  integer :: a=2, version=0
!!integer, :: x(n), y(n)
  integer, target, allocatable :: x(:), y(:)
  integer, pointer             :: xp(:), yp(:)

!! TODO 1:  Give x and y allocatable attributes
!!          and allocate them dynamically
   allocate( x(n), y(n) )
   xp=>x 
   yp=>y

   do i=1,n; x(i)=1; y(i)=1; enddo  !! init

   !! one thread executes the loop
   !! TODO 2: no map required for allocatable arrays
   !! TODO 2: Use array sections for last 1/2 of array
   !$omp target map(xp(n/2:n)) map(yp(n/2:n))
!! !$omp target
      do i=n/2,n; yp(i)=a*xp(i)+yp(i); enddo
   !$omp end target


   do i=n/2,n; if(y(i) /= 3) stop("y != 3"); enddo

#ifdef _OPENMP
   print*, "Passed OpenMP ", _OPENMP
#else
   print*, "Passed OpenMP off"
#endif

   !! TODO 2:  Do axpy on last have of vectors
   !!          Modify map, axpy loop and validate loop
end program
