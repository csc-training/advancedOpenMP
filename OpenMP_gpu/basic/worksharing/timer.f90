  module mod_timer
   ! Developed by Lars Koesterke @ TACC 
   
   private
   integer, parameter     :: m = 20
   
   type, public :: Timer_Collector
   
   private
   integer                         :: n = 0
   integer(8), dimension(2,m)      :: it
   integer(8)                      :: itr
   character(len=16), dimension(m) :: c
   
   contains
   
   procedure, public :: reset
   procedure, public :: start
   procedure, public :: stop
   procedure, public :: print
   
   endtype Timer_Collector
   
   contains
   
   subroutine reset(this)
   
   class(Timer_Collector) :: this
   this%n  = 0
   this%it = -1
   this%c  = 'undef'
   
   end subroutine
   
   
   subroutine start(this, c)
   
   class(Timer_Collector) :: this
   character(len=*) :: c
   character(len=16) :: c16
   
   this%n = this%n + 1
   if (this%n > m) then
     write (*,*) 'No more timers available'
     stop 'Fatal ERROR in method START of class CLS_TIMER'
   endif
   call system_clock(this%it(1,this%n), this%itr)
   ! to get PGI 11 going
   c16 = c
   this%c(this%n) = c16
   
   end subroutine
   
   
   subroutine stop(this)
   
   class(Timer_Collector) :: this
   
   call system_clock(this%it(2,this%n))
   
   end subroutine
   
   
   subroutine print(this)
   
   class(Timer_Collector) :: this
   
   write (*,*)
   write (*,'(a,es8.1)') 'Action           ::   time/s     Time resolution = ', 1./real(this%itr)
   write (*,'(a)')       '------'
   do i=1, this%n
     write (*,'(a,a, f12.6)') this%c(i), ' :: ',               &  !TODO change .6 to .precision
                              (real(this%it(2,i) - this%it(1,i))) / real(this%itr)
   enddo
   
   end subroutine
   
 end module mod_timer
