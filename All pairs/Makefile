Dijkstra:
	gcc -O2 -ffast-math -march=native allPairs.c -o unoptimized
	gcc -O2 -ffast-math -march=native allPairsOptimized.c -o optimized
	gcc -O2 -fopenmp -ffast-math -march=native allPairsParallell.c -o parallell
	gcc -O2 -fopenmp -ffast-math -march=native checkResult.c -o check


clean:
	rm -r unoptimized optimized parallell check