double precision function red_sum(n,a)
  integer          :: n
  double precision :: a(n)
  integer          :: i
! interface declares that this can be a "vector" function.
  interface
    double precision function fun(b)
      double precision  :: b
    end function fun
  end interface
      
  red_sum = 0.0d0
      
!  Reduction here causes a dependence
!  But SIMD units can now handle reductions!

  do i = 1,n
     red_sum = red_sum + fun(a(i))
  enddo

end function red_sum

!!https://software.intel.com/en-us/articles/openmp-40-new-features-supported-in-intel-compiler-160
