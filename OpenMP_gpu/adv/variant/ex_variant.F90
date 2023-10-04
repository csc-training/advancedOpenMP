!! not verified
module subs
  use omp_lib
contains
   subroutine vxv(v1, v2, v3)             !! base function
      integer :: v1(:),v2(:), v3:), i, n
      !$omp  declare variant( p_vxv ) match( construct={parallel} )
      !$omp  declare variant( t_vxv ) match( construct={target}   )
      n=size(v1)
      do i = 1,n; v3(i) = v1(i) * v2(i); enddo
   end subroutine

   subroutine p_vxv(v1, v2, v3)            !! function variant
      integer :: v1(:),v2(:), v3:), i, n
      n=size(v1)
      !$omp do 
      do i = 1,n; v3(i) = v1(i) * v2(i) * 3; enddo
   end subroutine

   subroutine t_vxv(v1, v2, v3)            !! function variant
      integer :: v1(:),v2(:), v3:), i, n
      !$omp declare target
      n=size(v1)
      !$omp distribute parallel for simd
      do i = 1,n; v3(i) = v1(i) * v2(i) * 2; enddo
   end subroutine
end module subs


program main
   use omp_lib
   use subs
   integer,parameter :: N = 100
   integer           :: v1(N), v2(N), v3(N)

   do i= 1,N; v1(i)= i; v2(i)= -i; v3(i)= 0;  enddo  !! init

   !$omp parallel
      call vxv(v1,v2,v3, n)
   !$omp end parallel

   !$omp target teams map(to: v1,v2) map(from: v3)
      call vxv(v1,v2,v3, n)
   !$omp end target teams

      call vxv(v1,v2,v3, n)

end program
