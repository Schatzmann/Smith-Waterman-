LDFLAGS = -g
CPFLAGS = -O3 -fopenmp

all: paralelo sequencial clean

paralelo: SmithParalelo.o 
	gcc SmithParalelo.o -o smithParalelo $(CPFLAGS) $(LDFLAGS)

sequencial: SmithSequencial.o
	gcc SmithSequencial.o -o smithSequencial $(CPFLAGS) $(LDFLAGS)

sequencial2: SmithSequencial_v2.o
	gcc SmithSequencial_v2.o -o smithSequencial_v2 $(CPFLAGS) $(LDFLAGS)

SmithSequencial.o: SmithSequencial.c
	gcc -c SmithSequencial.c $(CPFLAGS) $(LDFLAGS)

SmithSequencial_v2.o: SmithSequencial_v2.c
	gcc -c SmithSequencial_v2.c $(CPFLAGS) $(LDFLAGS)

SmithParalelo.o: SmithParalelo.c
	gcc -c SmithParalelo.c $(CPFLAGS) $(LDFLAGS)

clean:
	-rm *.o

purge:
	-rm smithSequencial smithParalelo smithSequencial_v2