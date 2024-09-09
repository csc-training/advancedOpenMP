program main
use omp_lib

!! TODO 3: display the "ENV" and affinity
   !! call omp_display_<TODO>;
   !! call omp_display_<TODO>;

!! TODO 1: get the thread number and number of threads
   !$omp parallel
     !!print*," omp_get_<TODO>, " out of " omp_get_<TODO>
   !$omp end parallel

end program main
