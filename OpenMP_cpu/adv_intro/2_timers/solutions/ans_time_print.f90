
include  "timer.f90"

program main

!! TODO 1a: Use the module in timer.f90 
!!          and instantiate a type(cls_timer) class
   use mod_timer
   type(cls_timer) timer

!! TODO 1b: Time a 1 second sleep
   call timer%start(" 1 sec sleep ");
      call sleep(1);
   call timer%stop();

!! TODO 1c: Now time a print statement
   call timer%start(" printf io   ");
      print*, " Hello Helsinki."
   call timer%stop();

!! TODO 1d: report measurements
   call timer%print();

end program main
