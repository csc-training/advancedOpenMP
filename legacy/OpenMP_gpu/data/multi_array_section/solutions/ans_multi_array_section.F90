program main
  integer, parameter :: n=16
  integer :: a=2, version=0
  integer :: x(n), y(n)

   do i=1,n; y(i)=1; enddo  !! init

   !! one thread executes the loop
   !! TODO 1:  map all of y as tofrom, and only approriately needed section of x

   !$omp target map(to:x(1:n/4),x(n/2+1:n)) map(tofrom:y)
    do i=1,    n/4; x(i)=1; enddo
    do i=n/2+1,n  ; x(i)=1; enddo

    do i=1,    n/4; y(i)=a*x(i)+y(i); enddo
    do i=n/2+1,n  ; y(i)=a*x(i)+y(i); enddo
   !$omp end target

   do i=1,    n/4; if(y(i) /= 3) stop("y != 3"); enddo
   do i=n/2+1,n  ; if(y(i) /= 3) stop("y != 3"); enddo

#ifdef _OPENMP
   print*, "Passed OpenMP ", _OPENMP
#else
   print*, "Passed OpenMP off"
#endif

end program
