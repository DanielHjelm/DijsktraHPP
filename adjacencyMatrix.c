// Adjacency matrix

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>



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
                // Create random number between 0-10
                int randomNumber = rand() % 10;
                // Put the random number in the matrix
                matrix[i][j] = randomNumber;
                matrix[j][i] = randomNumber;  
            }

        }
    }

}