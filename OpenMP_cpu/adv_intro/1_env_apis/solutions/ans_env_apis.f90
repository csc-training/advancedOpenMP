program main
use omp_lib

!! TODO 3: display the "ENV" and affinity
   !! call omp_display_<TODO>;
   !! call omp_display_<TODO>;
      call omp_display_env(.TRUE.)   !!Lumi not supported in cce 15.0
      call omp_display_affinity("")

!! TODO 1: get the thread number and number of threads
   !$omp parallel
     !!print*," omp_get_<TODO>, " out of " omp_get_<TODO>
       print*, omp_get_thread_num(), " out of ", omp_get_num_threads()
   !$omp end parallel

end program main
