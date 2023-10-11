#NVCC   = nvcc
#CFLAGS = -O2

CPP=clang++
OMP_FLAG=-fopenmp
 OMP_OFF=-fopenmp-targets=nvptx64
 CCFLAGS=-O2

#CPP=clang++
#OMP_FLAG=-fopenmp
# OMP_OFF=
# CCFLAGS=-O2


add_c: add.o
	$(CPP)    -o $@ $(OMP_FLAG) $(OMP_OFF) add.o
add.o: add.cpp
	$(CPP) -c -o $@ $(OMP_FLAG) $(OMP_OFF) $? $(CCFLAGS)

clean:
	rm -f add_c *.o
