!unverified

function dotprod(B,C,N) result(sum)
   real    :: B(N), C(N), sum
   integer :: N, i
   sum = 0.0e0
!! TODO 1a-c map B and C, make scalars tofrom by default
!!           and include a reduction if necessary
      do i = 1,N
         sum = sum + B(i) * C(i)
      end do
end function

! Note:  The variable sum is now mapped with tofrom from the defaultmap
!  clause on the combined target teams construct, for correct 
!  execution with 4.5 (and pre-4.5) compliant compilers. See Devices Intro.

program main
   integer, parameter ::  N=1024*1024
   integer :: i
   real    :: sum, B(N),C(N)  !!init vv

   do i=1,N;  B(i)=1.0e0; C(i)=1.0e0;  end do

   sum=dotprod(B,C,N)

   print*,"N= ", N, ", sum= ",sum

end program main
