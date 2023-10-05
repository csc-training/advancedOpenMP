subroutine add_floats(a,b,c,d,e,n)
real,pointer,dimension(:) :: a,b,c,d,e
!   Note, a,b,c,d and e are pointers
!   With 5 pointers, compiler gives up on vectorization
!   Need to force the compiler to SIMDize it.

!   !$omp ??
    do i = 1,n
       a(i) = a(i) + b(i) + c(i) + d(i) + e(i)
    end do
end subroutine
