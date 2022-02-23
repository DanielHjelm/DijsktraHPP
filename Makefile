Dijkstra:
	gcc -O2 -ffast-math -march=native serialDijkstra.c -o unoptimized
	gcc -O2 -ffast-math -march=native serialDijkstraOptimized.c -o optimized

clean:
	rm -r unoptimized optimized