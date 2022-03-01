#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

// Function that checks that the output array is the same. 
int CheckMatrix(int **matrix1, int **matrix2, int **matrix3, int size){
    int i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            if(matrix1[i][j] != matrix2[i][j] || matrix1[i][j] != matrix3[i][j] || matrix2[i][j] != matrix3[i][j]){
                return 0;
            }

        }
            
        }
    return 1;
}


//******************************************************************************//
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
                printf("%5s", "Inf");
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
    printf("These are the results: \n");
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
    int i, j, k, l; 

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

        // Intiliaze index for the minimum
        int min = 0;

        // Find the minimum distance's index only if it is already not visited.
        for (k = 0; k < size; k++){
            if(visitedArray[k]==0 && distanceArray[k]<= minimum ){
                // Update minimum
                minimum = distanceArray[k];
                // Update the index
                min = k;
            }
        }

        // Update it so it is visited
        visitedArray[min] = 1;

        // For the current position, check all other positions and update if conditions are met
        for (l = 0; l < size; l++){

            // Condition for updating the value in distanceArray:
            // 1. The pathway from the start through min to l is smaller than the saved distance in distanceArray
            // 2. l is not yet visited (not in visitedArray)
            // 3. min and l are actually adjacent
            if( visitedArray[l] == 0 &&
                distanceArray[min]+matrix[min][l] < distanceArray[l] &&
                matrix[min][l] && 
                distanceArray[min] != 10000){
                
                    distanceArray[l] = distanceArray[min] + matrix[min][l];


            }

        }

        
    }


}

// The Dijkstras algorithm for finding the shortest path 
void DijkstrasAlgorithmOptimized(int size, int **matrix, int *distanceArray, int start){
    
    // Loop variables
    int i, j, k, l; 

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
        int i;
        int min = 0;

        // Find the minimum distance's index only if it is already not visited.
        for (k = 0; k < size; k++){
            if(visitedArray[k]==0 && distanceArray[k]<= minimum ){
                // Update minimum
                minimum = distanceArray[k];
                // Update the index
                min = k;
            }
        }
        
        // Update so it is visited
        visitedArray[min] = 1;
        
        // Fetch the distance of the minimum position:
        int distMin = distanceArray[min];
        
        // For the current position, check all other positions and update if conditions are met
        for (l = 0; l < size; l++){

            // Condition for updating the value in distanceArray:
            // 1. l is not yet visited (not in visitedArray)
            // 2. min and l are actually adjacent
            // 3. The pathway from the start through min to l is smaller than the saved distance in distanceArray
            if(distMin+matrix[min][l] < distanceArray[l] &&
                visitedArray[l] == 0 &&
                matrix[min][l] && 
                distMin != 10000){
                
                    distanceArray[l] = distMin + matrix[min][l];


            }

        }

        
    }
   
}

//******************************************************************************//
int main(int argc, char *argv[])
{   
    // Check input arguments
    if (argc != 3)
    {
        printf("Please provide only the size of the adjenceny matrix and the number of threads\n");
        exit(EXIT_FAILURE);
    }
    
    // Fetch the input arguments
    int size = atoi(argv[1]);
    int numberOfThreads = atoi(argv[2]);
    
    // Initiliaze variables
    int i;
    int **matrix;
    int **distanceMatrix;
    int **distanceMatrixOptimized;
    int **distanceMatrixParallell;

    // Allocate memory for the matrices
    matrix= malloc(size * sizeof(int *));
    distanceMatrix = malloc(size * sizeof(int *));
    distanceMatrixParallell = malloc(size * sizeof(int *));
    distanceMatrixOptimized =  malloc(size * sizeof(int *));


    for (i = 0; i < size; i++)
    {
        matrix[i] = malloc(size * sizeof(int));
        distanceMatrix[i] = malloc(size * sizeof(int));
        distanceMatrixParallell[i] = malloc(size * sizeof(int));
        distanceMatrixOptimized[i] = malloc(size * sizeof(int *));

    }

   
    // Create adjacency matrix:
    
    GenerateAdjacencyMatrix(size, matrix);


    // Perform Dijsktra on every start position
    int start;
    #pragma omp parallel for num_threads(numberOfThreads)
    for(start=0; start < size; start++) {
        
        DijkstrasAlgorithmOptimized(size, matrix, distanceMatrixParallell[start], start);

    }

    int start2;
    for(start2=0; start2 < size; start2++) {
        
        DijkstrasAlgorithm(size, matrix, distanceMatrix[start2], start2);

    }

    int start3;
    for(start3=0; start3 < size; start3++) {
        
        DijkstrasAlgorithmOptimized(size, matrix, distanceMatrixOptimized[start3], start3);

    }


    // Check the output
    
    if(CheckMatrix(distanceMatrix, distanceMatrixParallell, distanceMatrixOptimized, size)){
        printf("The arrays are the same, everything is OK!\n");
    }else {
        printf("The arrays are not the same, something is wrong!\nn");

    }


    // Free memory
    
    for (i = 0; i < size; i++)
    {
        free(matrix[i]);
        free(distanceMatrix[i]);
        free(distanceMatrixParallell[i]);
    }
    free(matrix);
    free(distanceMatrix);
    free(distanceMatrixParallell);
    
    return 0;
}