functions:
	gcc -o functions functions.h

serialDijkstra: functions
	gcc functions.h serialDijkstra.c -o serialDijkstra

clean: 
	rm serialDijkstra functions
