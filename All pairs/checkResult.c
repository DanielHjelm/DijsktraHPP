#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

int CheckArray(int array1[], int array2[], int size){
    int i;
    for (i = 0; i < size; i++){
            if(array1[i] != array2[i]){
                return 0;
            }
        }
    return 1;
}



//******************************************************************************//
// General functions

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


// The Dijkstras algorithm for finding the shortest path 
void DijkstrasAlgorithmParallel(int size, int **matrix, int *distanceArray, int start, int numberOfThreads){
    // Loop variables
    int i, j, k, l; 

    // Array representing if the position is visited or not
    int visitedArray[size];

    // Initiliaze the distanceArray with large since we have no values for it yet
    // Initiliaze the visitedArray with false (0) since no position is visited yet
    #pragma omp parallel for num_threads(numberOfThreads)
    for (i = 0; i < size; i++){
        distanceArray[i] = 10000;
        visitedArray[i] = 0;
    }

    // The distance from the starting position (start) to itself is set to zero
    distanceArray[start] = 0;

    // Loop through every position to find the position with the shortest distance
    #pragma omp parallel for num_threads(numberOfThreads)
    for (j = 0; j < size-1; j++){

        // Initiliaze minimum with large number
        int minimum = 10000;
        // Intiliaze loop variable and index for the minimum
        int min;

        // Find the minimum distance's index only if it is already not visited.
        // Can't be parallelized due to the update of minumum and min
        for (l = 0; l < size; l++){
            if(visitedArray[l]==0 && distanceArray[l]<= minimum ){
                // Update minimum
                minimum = distanceArray[l];
                // Update the index
                min = l;
            }
        }
        
        // Update so it is visited
        visitedArray[min] = 1;
        
        // Fetch the distance of the minimum position:
        int distMin = distanceArray[min];
        
        // For the current position, check all other positions and update if conditions are met
        // #pragma omp parallel for num_threads(numberOfThreads)
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

// The Dijkstras algorithm for finding the shortest path 
void DijkstrasAlgorithmSerial(int size, int **matrix, int *distanceArray, int start){
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
// Main
int main(int argc, char *argv[])
{   
    // Check input arguments
    if (argc != 4)
    {
        printf("Please provide only the size of the adjenceny matrix, the starting position and number of threads \n");
        exit(EXIT_FAILURE);
    }
    
    // Fetch the input arguments
    int size = atoi(argv[1]);
    int start = atoi(argv[2]);
    int numberOfThreads = atoi(argv[3]);


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
    int *distanceArrayParallel = malloc(size * sizeof(int *));
    int *distanceArraySerial = malloc(size * sizeof(int *));

    // Create adjacency matrix:
    GenerateAdjacencyMatrix(size, matrix);

    // Activate nested parallelism
    // omp_set_nested(1);

    // Perform Dijkstras
    DijkstrasAlgorithmParallel(size, matrix, distanceArrayParallel, start, numberOfThreads);
    DijkstrasAlgorithmSerial(size, matrix, distanceArraySerial, start);

    int result = CheckArray(distanceArrayParallel, distanceArraySerial, size);
    
    if(result){
        printf("The distance arrays are the same, everything is OK!\n");
        
    }else{
        printf("The distance arrays are not the same, something is wrong!\n");
    }
    // Free memory
    for (i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(distanceArraySerial);
    free(distanceArrayParallel);
    
    return 0;
}
// ****************************************************************************** //

