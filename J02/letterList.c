/* Authors: Juliette and Lola
Description: Takes word and creates matrix with word at bottom, top, and accross.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char input[32];
    int rowsCol;
    char *matrix;
    
    printf("Enter a string: ");
    scanf("%s", input);
    rowsCol = strlen(input);
    
    matrix = malloc(sizeof(char) * rowsCol * rowsCol);
    if (matrix == NULL){
        printf("error\n");
        exit(1);
    }
    
    for (int i = 0; i < rowsCol; i++) {
        for (int j = 0; j < rowsCol; j++) {
            matrix[i * rowsCol + j] = ' ';
        }
    }

    strcpy(matrix, input);
    matrix[1 * rowsCol + 0] = ' ';
    
    for (int i = 0; i < rowsCol; i++){
        char letter = input[i];
        matrix[i * rowsCol + i] = letter;
    }
    
    for (int j = 0; j < rowsCol; j++){
        matrix[(rowsCol-1) * rowsCol + j] = input[j];
    }
    
    
     for (int i = 0; i < rowsCol; i++) {
        for (int j = 0; j < rowsCol; j++) {
            printf("%c ", matrix[i * rowsCol + j]);
        }
        printf("\n");
    }
    
    free(matrix);
    matrix = NULL;

    return 0;
}