// Serial implementation of the Dijkstras search algorithm
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "functions.h"

// 
static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}
// Function that prints the content of a matrix
void printMatrix(int size, int **matrix) {
    int r, c;
    for (r=0; r<size; r++)
    {
        for(c=0; c<size; c++)
        {
            printf("%d     ", matrix[r][c]);
        }
        printf("\n");
    }
}


// Function that finds the position with the minimum distance 
int MinimumDistance(int distanceArray[], int visitedArray[], int size){
    // Initilize variables
    int minimum = INT_MAX;
    int i, index;

    // Find the index of the minimum distance if it i smaller than the value in distanceArray
    // and if we have not already visited it
    for (i = 0; i < size; i++){
        if(distanceArray[i]<= minimum && visitedArray[i]==0){
            minimum = distanceArray[i];
            index = i;
        }

    }
    return index;


}
// Function that prints the result of Dijkstra
void PrintDijkstra(int distanceArray[], int size)
{
    printf("Position \t\t Distance from the start\n");
    for (int i = 0; i < size; i++)
        printf("%d \t\t\t %d\n", i, distanceArray[i]);
}

// The Dijkstras algorithm for finding the shortest path 
void DijkstrasAlgorithm(int size, int **matrix, int start){
    // Loop variables
    int i, j, k; 
    // Array representing the shortest distance from the start to a position (pos) in graph
    int distanceArray[size];

    // Array representing if the position is visited or not
    int visitedArray[size];

    // Initiliaze the distanceArray with Infinity since we have no values for it
    // Initiliaze the visitedArray with false since no position is visited yet
    for (i = 0; i < size; i++){
        distanceArray[i] = INT_MAX;
        visitedArray[i] = 0;
    }

    // The distance from the starting position (start) to itself is set to zero
    distanceArray[start] = 0;

    // Loop through every position to find the shortest distance
    for (j = 0; j < size-1; j++){

        // Fetch the position with minimum distance from the MinimumDistance function and
        // updated it so it is visited
        int min  = MinimumDistance(distanceArray, visitedArray, size);
        visitedArray[min] = 1;

        // For the picked position, update all the adjacent values
        for (k = 0; k < size; k++){

            // Condition for updating the value in distanceArray:
            // 1. k is not yet visited (not in visitedArray)
            // 2. min and k are actually adjacent
            // 3. The pathway from the start through min to k is smaller than the saved distance in distanceArray
            if(visitedArray[k] == 0 &&
                matrix[min][k] && 
                distanceArray[min] != INT_MAX &&
                distanceArray[min]+matrix[min][k] < distanceArray[k]){
                
                    distanceArray[k] = distanceArray[min] + matrix[min][k];


            }

        }

        
    }

    // Print the Dijkstra
    PrintDijkstra(distanceArray, size);


}

int main()
{   
    // Initiliaze variables
     int size, i;
     int **matrix;
    // Fetch the size of the adjaceny
    printf("Enter the size of the adjaceny matrix: ");
    scanf("%d", &size);
    
    // Allocate memory for the matrix
    matrix= malloc(size * sizeof(int *));

    for (i = 0; i < size; i++)
    {
        matrix[i] = malloc(size * sizeof(int));
    }
   
    // Create adjacency matrix:
    GenerateAdjacencyMatrix(size, matrix);

    // Print adjaceny matrix
    // printMatrix(size, matrix);

    // Start timing
    double startTime = get_wall_seconds();

    // Perform Dijsktras
    DijkstrasAlgorithm(size, matrix, 0);
    double endTime = get_wall_seconds() - startTime;
    printf("Time: %f for matrix size: %d\n", endTime, size);
    return 0;
}