program war
integer x

 x =1

 !$omp parallel
   !$omp single

      !$omp task shared(x) depend(<???>: x)
         x = 2
      !$omp end task

      !$omp task shared(x) depend(<???>: x)
         print*,"WaR      dependence x = ", x
      !$omp end task


   !$omp end single
 !$omp end parallel

end program
