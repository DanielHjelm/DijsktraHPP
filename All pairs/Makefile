CC = gcc
CFLAGS = -O2 -ffast-math -march=native -funroll-all-loops
CFLAGSPARALLEL = -O2 -fopenmp -ffast-math -march=native -funroll-all-loops

Dijkstra:
	$(CC) $(CFLAGS) allPairs.c -o unoptimized
	$(CC) $(CFLAGS) allPairsOptimized.c -o optimized
	$(CC) $(CFLAGSPARALLEL) allPairsParallell.c -o parallell
	$(CC) $(CFLAGSPARALLEL)  checkResult.c -o check


clean:
	rm -r unoptimized optimized parallell check