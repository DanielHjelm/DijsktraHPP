/// Serial implementation of the Dijkstras search algorithm 
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

// Function that generates a random adjacency matrix
void GenerateAdjacencyMatrix(int size, int **matrix) {
    // Initiliaze matrix and loop variables
    int i;
    int j;
    // Initialize random number generator
    srand(0);
    // Create adjacency matrix
    for(i = 0; i < size; i++)
    {
        for(j = i; j < size; j++)
        {   
            // Distance to itself is 0
            if(i == j){
                matrix[i][j] = 0;
            }

            else{
                // Create random number between 0-5
                int randomNumber = rand() % 5;
                // Put the random number in the matrix
                matrix[i][j] = randomNumber;
                matrix[j][i] = randomNumber;  
            }

        }
    }

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
int MinimumDistance(int distanceArray[], int visitedArray[], int size, int numberOfThreads){
    // Initilize variables
    int minimum = INT_MAX;
    int i, index;

    // Find the index of the minimum distance if it i smaller than the value in distanceArray
    // and if we have not already visited it
    #pragma omp parallel for num_threads(numberOfThreads)
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
void DijkstrasAlgorithm(int size, int **matrix, int *distanceArray, int numberOfThreads, int start){
    // Loop variables
    int i, j, k; 

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
        int min  = MinimumDistance(distanceArray, visitedArray, size, numberOfThreads);
        visitedArray[min] = 1;

        // For the picked position, update all the adjacent values
        #pragma omp parallel for num_threads(numberOfThreads)
        for (k = 0; k < size; k++){

            // Condition for updating the value in distanceArray:
            // 1. The pathway from the start through min to k is smaller than the saved distance in distanceArray
            // 2. k is not yet visited (not in visitedArray)
            // 3. min and k are actually adjacent
            if(distanceArray[min]+matrix[min][k] < distanceArray[k] &&
                visitedArray[k] == 0 &&
                matrix[min][k] && 
                distanceArray[min] != INT_MAX ){
                
                    distanceArray[k] = distanceArray[min] + matrix[min][k];


            }

        }

        
    }

    // Print the Dijkstra
    // PrintDijkstra(distanceArray, size);


}

int main(int argc, char *argv[])
{   
    // Check input arguments
    if (argc != 3)
    {
        printf("Please provide the size of the adjenceny matrix and the number of threads\n");
        exit(EXIT_FAILURE);
    }
    // Initiliaze variables
     int i;
     int **matrix;
     int size = atoi(argv[1]);
     int numberOfThreads = atoi(argv[2]);
    
    // Allocate memory for the matrix
    matrix= malloc(size * sizeof(int *));

    for (i = 0; i < size; i++)
    {
        matrix[i] = malloc(size * sizeof(int));
    }

     // Array representing the shortest distance from the start to a position (pos) in the matrix
    int *distanceArray = malloc(size * sizeof(int *));
   
    // Create adjacency matrix:
    GenerateAdjacencyMatrix(size, matrix);

    // Print adjaceny matrix
    // printMatrix(size, matrix);

    // Start timing
    double startTime = omp_get_wtime();

    // Perform Dijsktras
    DijkstrasAlgorithm(size, matrix, distanceArray, numberOfThreads ,0);

    // Stop timing
    double endTime = omp_get_wtime() - startTime;
    printf("Time: %f for matrix size: %d and %d threads\n", endTime, size, numberOfThreads);

    // int j;
    // for (i = 0; i < size; i++){
    //     printf("%d\n", distanceArray[i]);
    // }

    // Free memory
    
    for (i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(distanceArray);
    
    return 0;
}