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
    srand(1);
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
                int randomNumber = rand() % 10;
                if (randomNumber > 4){
                    // Put the random number in the matrix
                    matrix[i][j] = randomNumber+1;
                    matrix[j][i] = randomNumber-3;
                } else {
                    matrix[i][j] = 10000;
                    matrix[j][i] = 10000;
                }
            }

        }
    }

}

//******************************************************************************//
// Helper function for printing the result to check if everything seems good //

// Function that prints the content of a matrix
void PrintMatrix(int size, int **matrix) {
    int r, c;
    for (r=0; r<size; r++)
    {
        for(c=0; c<size; c++)
        {
            if(matrix[r][c] == 10000) {
                printf("%5s", "X");
            } else {
                printf("%5d", matrix[r][c]);
            }
           
        }
        printf("\n");
    }
}

// Function printing the results from Dijkstras
void PrintDijsktra(int **distanceMatrix, int size)
{
    printf("Dijkstra:\n");
    printf("You picked an adjcency matrix of size %d \n", size);
    printf("These are the results: \n\n");
    int r, c;
    for (r=0; r<size; r++)
    {
        for(c=0; c<size; c++)
        {   
            // Print an X if there is not connection between the nodes
            if(distanceMatrix[r][c] == 10000) {
                printf("%5s", "X");
            } else {
                printf("%5d", distanceMatrix[r][c]);
            }
           
        }
        printf("\n");
    }
    
}

//******************************************************************************//

// The Dijkstras algorithm for finding the shortest path 
void DijkstrasAlgorithm(int size, int **matrix, int *distanceArray, int start){
    // Loop variables
    int i, j, k; 

    // Array representing if the position is visited or not
    int visitedArray[size];

    // Initiliaze the distanceArray with large since we have no values for it yet
    // Initiliaze the visitedArray with false (0) since no position is visited yet
    for (i = 0; i < size; i++){
        distanceArray[i] = 10000;
        visitedArray[i] = 0;
    }

    // The distance from the starting position (start) to itself is set to zero
    distanceArray[start] = 0;

    // Loop through every position to find the position with the shortest distance
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
        
        // Update so it is visited
        visitedArray[min] = 1;
        
        // Fetch the distance of the minimum position:
        int distMin = distanceArray[min];
        
        // For the current position, check all other positions and update if conditions are met
        for (k = 0; k < size; k++){

            // Condition for updating the value in distanceArray:
            // 1. k is not yet visited (not in visitedArray)
            // 2. min and k are actually adjacent
            // 3. The pathway from the start through min to k is smaller than the saved distance in distanceArray
            if(distMin+matrix[min][k] < distanceArray[k] &&
                visitedArray[k] == 0 &&
                matrix[min][k] && 
                distMin != 10000){
                
                    distanceArray[k] = distMin + matrix[min][k];


            }

        }

        
    }


}

//******************************************************************************//
int main(int argc, char *argv[])
{   
    // Check input arguments
    if (argc != 2)
    {
        printf("Please provide only the size of the adjenceny matrix\n");
        exit(EXIT_FAILURE);
    }
    
    // Fetch the input arguments
    int size = atoi(argv[1]);
    
    // Initiliaze variables
    int i;
    int **matrix;
    int **distanceMatrix;

    // Allocate memory for the matrix and distanceMatrix
    matrix= malloc(size * sizeof(int *));
    distanceMatrix = malloc(size * sizeof(int *));

    for (i = 0; i < size; i++)
    {
        matrix[i] = malloc(size * sizeof(int));
        distanceMatrix[i] = malloc(size * sizeof(int));
    }

   
    // Create adjacency matrix:
    
    GenerateAdjacencyMatrix(size, matrix);

    // Print adjaceny matrix
    printf("\n");
    PrintMatrix(size, matrix);
    printf("\n");
    // Start timing
    double startTime = get_wall_seconds();

    // Perform Dijsktra on every start position
    int start;
    for(start=0; start < size; start++) {
        
        DijkstrasAlgorithm(size, matrix, distanceMatrix[start], start);

    }
    
    // Stop timing
    double endTime = get_wall_seconds() - startTime;

    printf("Time: %f for matrix size: %d\n", endTime, size);
    
    // Print the result
    printf("\n");
    PrintDijsktra(distanceMatrix, size);
    printf("\n");
    // Free memory
    
    for (i = 0; i < size; i++)
    {
        free(matrix[i]);
        free(distanceMatrix[i]);
    }
    free(matrix);
    free(distanceMatrix);
    
    return 0;
}