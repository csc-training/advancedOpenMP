#NVCC   = nvcc
#CFLAGS = -O2

#TACC LS6 (clang++ 16)
ifneq ("$(TACC_SYSTEM)","")
   ifeq ($(TACC_SYSTEM),ls6)
     ifeq ($(shell clang++ -v 2>&1 | grep -c "clang version"), 1)
         CC       =  clang++
         CCFLAGS  = -O2
         OMP_FLAG = -fopenmp
         OMP_OFF  = -fopenmp-targets=nvptx64
      endif
   endif
endif

#LUMI
ifneq ("$(LUMI_LMOD_FAMILY_PRGENV)","")
 CC       =  CC
 CCFLAGS  = -O2
 OMP_FLAG = -fopenmp
 OMP_OFF  =
endif


add_c: add.o
	$(CC)    -o $@ $(OMP_FLAG) $(OMP_OFF) add.o $(PIE)
add.o: add.cpp
	$(CC) -c -o $@ $(OMP_FLAG) $(OMP_OFF) $? $(CCFLAGS) $(PIE)

clean:
	rm -f add_c *.o
#https://www.gnu.org/software/make/manual/html_node/index.html#SEC_Contents
#https://stackoverflow.com/questions/5188267/checking-the-gcc-version-in-a-makefile
