Dijkstra:
	gcc -O2 -ffast-math -march=native serialDijkstra.c -o unoptimized
	gcc -O2 -ffast-math -march=native serialDijkstraOptimized.c -o optimized
	# gcc -O2 -fopenmp -ffast-math -march=native parallelDijkstra.c -o parallel


clean:
	rm -r unoptimized optimized parallel