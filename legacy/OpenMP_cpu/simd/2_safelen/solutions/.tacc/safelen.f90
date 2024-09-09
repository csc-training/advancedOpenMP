
subroutine transform(as,ac, j,offset)

integer,parameter :: N=1000000
integer           :: j,offset
double precision  :: as(n,n),ac(n,n)
!  offset will always be 16 or greater
integer :: i

   !$omp simd safelen(16)
   do i = offset, N-offset
      as(i,j) = as(i-offset,j) + sin(as(i,j))
      ac(i,j) = ac(i+offset,j) + cos(ac(i,j))
   end do

end subroutine
