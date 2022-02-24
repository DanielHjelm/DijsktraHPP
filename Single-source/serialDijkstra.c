/// Serial implementation of the Dijkstras search algorithm 
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

//******************************************************************************//
// Time taking function
static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

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

//******************************************************************************//
// Helper function for printing the result to check if everything seems good //

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

// Function printing the results from Dijkstras
void PrintDijkstra(int distanceArray[], int size, int start)
{
    printf("Dijsktras:\n");
    printf("You picked an adjcency matrix of size %d and starting position %d. \n", size, start);
    printf("These are the results: \n");
    for (int i = 0; i < size; i++)
        printf("%d -> %d: %d\n", start, i+1, distanceArray[i]);
}

//******************************************************************************//

// The Dijkstras algorithm for finding the shortest path 
void DijkstrasAlgorithm(int size, int **matrix, int *distanceArray, int start){
    // Loop variables
    int i, j, k; 

    // Array representing if the position is visited or not
    int visitedArray[size];

    // Initiliaze the distanceArray with large number since we have no values for it yet
    // Initiliaze the visitedArray with false since no position is visited yet
    for (i = 0; i < size; i++){
        distanceArray[i] = 10000;
        visitedArray[i] = 0;
    }

    // The distance from the starting position (start) to itself is set to zero
    distanceArray[start] = 0;

    // Loop through every position to find the shortest distance
    for (j = 0; j < size-1; j++){

        // Initiliaze minimum with large number
        int minimum = 10000;
        // Intiliaze loop variable and index for the minimum
        int i, min;

        // Find the minimum distance's index only if it is already not visited.
        for (i = 0; i < size; i++){
            if(visitedArray[i]==0 && distanceArray[i]<= minimum ){
                // Update minimum
                minimum = distanceArray[i];
                // Update the index
                min = i;
            }
        }

        // Update it so it is visited
        visitedArray[min] = 1;

        // For the current position, check all other positions and update if conditions are met
        for (k = 0; k < size; k++){

            // Condition for updating the value in distanceArray:
            // 1. The pathway from the start through min to k is smaller than the saved distance in distanceArray
            // 2. k is not yet visited (not in visitedArray)
            // 3. min and k are actually adjacent
            if( visitedArray[k] == 0 &&
                distanceArray[min]+matrix[min][k] < distanceArray[k] &&
                matrix[min][k] && 
                distanceArray[min] != 10000){
                
                    distanceArray[k] = distanceArray[min] + matrix[min][k];


            }

        }

        
    }


}

int main(int argc, char *argv[])
{   
    // Check input arguments
    if (argc != 3)
    {
        printf("Please provide only the size of the adjenceny matrix and the starting position. \n");
        exit(EXIT_FAILURE);
    }
    
    // Fetch the input arguments
    int size = atoi(argv[1]);
    int start = atoi(argv[2]);

    // Check so that the starting position is actually valid.
    if (start >= size || start < 0) {
        printf("The given start position is not a valid position. Please give a start position between 0 and %d. \n", size);
        exit(EXIT_FAILURE);
    }
    
    // Initiliaze variables
    int i;
    int **matrix;
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
    printMatrix(size, matrix);

    // Start timing
    double startTime = get_wall_seconds();

    // Perform Dijsktras
    DijkstrasAlgorithm(size, matrix, distanceArray, start);

    // Stop timing
    double endTime = get_wall_seconds() - startTime;

    printf("Time: %f for matrix size: %d\n", endTime, size);
    
    // Print the Dijkstra
    PrintDijkstra(distanceArray, size, start);

    // Free memory
    
    for (i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(distanceArray);
    
    return 0;
}