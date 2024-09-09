module vec_mod

   integer, parameter :: N=100    !N must be even
   type v_t
     integer          ::  len
     double precision ::  a(N)
   end type

 !! TODO 2a:
 !! create mapper with lef_id identifier, for derived type v_t
 !! with a map of array section a(1:N/2)
!!$omp  declare mapper( left_id:  v_t :: v) map(tofrom:   v%a(1:N/2))
 !$omp  declare mapper( left_id:  v_t :: v) map(tofrom: v,v%a(1:N/2))

end module

program main
  use  vec_mod
  type(v_t) :: my_vec 

   !! TODO 2a: map my_vec, using the identifier left_id
   !! with map type of tofrom
   !$omp target map(mapper(left_id),tofrom: my_vec)
    do j = 1,N/2
       my_vec%a(j)= 9.0e0
    enddo
   !$omp end target

   print*, "my_vec%a(1) = ", my_vec%a(1)

end program main
