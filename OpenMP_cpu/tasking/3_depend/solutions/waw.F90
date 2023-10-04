program waw
integer x

 x =1

 !$omp parallel
   !$omp single

      !$omp task shared(x) depend(out: x)
         x = 2
      !$omp end task

      !$omp task shared(x) depend(out: x)
         print*,"WaW      dependence x = ", x
      !$omp end task


   !$omp end single
 !$omp end parallel

end program
