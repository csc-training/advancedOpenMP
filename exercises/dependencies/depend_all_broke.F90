program dependall

integer x

!$omp parallel

   x=1
   !$omp single

      !$omp task shared(x) depend(out: x)
         x = 2
      !$omp end task

      !$omp task shared(x) depend( in: x)
         print*,"a RaW x(2) = ", x
      !$omp end task

   !$omp end single


   x = 1
   !$omp single

      !$omp task shared(x) depend( in: x)
         x = 2
      !$omp end task

      !$omp task shared(x) depend(out: x)
         print*,"b WaR x(2) = ", x
      !$omp end task

   !$omp end single


   x =1
   !$omp single

      !$omp task shared(x) depend(out: x)
         x = 2
      !$omp end task

      !$omp task shared(x) depend(out: x)
         print*,"c WaW x(2) = ", x
      !$omp end task

   !$omp end single


   x =1
   !$omp single

      !$omp task shared(x) depend( in: x)
         x = 2
      !$omp end task

      !$omp task shared(x) depend( in: x)
         print*,"d RaR x(1 or 2) = ", x
      !$omp end task

   !$omp end single


!$omp end parallel

end program

