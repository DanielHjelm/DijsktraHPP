Dijkstra:
	gcc -O2 -ffast-math -march=native -funroll-all-loops allPairs.c -o unoptimized
	gcc -O2 -ffast-math -march=native -funroll-all-loops allPairsOptimized.c -o optimized
	gcc -O2 -fopenmp -ffast-math -march=native -funroll-all-loops allPairsParallell.c -o parallell
	gcc -O2 -fopenmp -ffast-math -march=native -funroll-all-loops checkResult.c -o check


clean:
	rm -r unoptimized optimized parallell check