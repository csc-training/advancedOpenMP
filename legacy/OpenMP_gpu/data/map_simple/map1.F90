program main
   integer :: a(2)=[9,9]

   !! TODO 1a:  map the data tofrom (same as implicit)
   !! TODO 1b:  map the data from   (optimal)
   !! TODO 1c:  map the data to     (not what you want)
   !! TODO 4:  specify defaultmap(none)  only
   !! TODO 5:  specify defaultmap(from:aggregate) only

     a(1)=1; a(2)=0;

   print*, a(1), a(2)
end program main
