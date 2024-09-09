program ex5
use omp_lib

integer, parameter :: N=25000

double precision   :: sum = 0.0d0

   !$omp  parallel do reduction(+:sum)
   do i = 1,N
     sum = sum + i
   end do

   print*,"sum=",sum

end program
