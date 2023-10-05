
subroutine transform(as,ac, j,offset)

integer,parameter :: N=1000000
integer           :: j,offset(N)
double precision  :: as(n,n),ac(n,n)
!  offset will always be at least 8 or greater
integer :: i

   do i = 9, N-9
      as(i,j) = as(i-offset(i),j) + (as(i,j))
      ac(i,j) = ac(i+offset(i),j) + (ac(i,j))
   end do

end subroutine
