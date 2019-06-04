LDFLAGS = -g
CPFLAGS = -O3 -fopenmp

all: paralelo sequencial clean

paralelo: SmithParalelo.o 
	gcc SmithParalelo.o -o smithParalelo $(CPFLAGS) $(LDFLAGS)

sequencial: SmithSequencial.o
	gcc SmithSequencial.o -o smithSequencial $(CPFLAGS) $(LDFLAGS)

SmithSequencial.o: SmithSequencial.c
	gcc -c SmithSequencial.c $(CPFLAGS) $(LDFLAGS)

SmithParalelo.o: SmithParalelo.c
	gcc -c SmithParalelo.c $(CPFLAGS) $(LDFLAGS)

clean:
	-rm *.o

purge:
	-rm smithSequencial smithParalelo