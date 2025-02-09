/*----------------------------------------------
 * Author: Juliette Ortiz
 * Date: February 8, 2025
 * Takes user input and creates matrix with manhattan distance from W
 *
 * Used Stack overflow for int to char conversion
 * https://stackoverflow.com/questions/2279379/how-to-convert-integer-to-char-in-c
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>


int main() {
  int rows; 
  int columns;
  int wampusI; //W row index`
  int wampusJ; //W column index
  char *matrix; //matrix pointer

  //user input
  printf("Number is rows: ");
  scanf("%d", &rows);
  printf("Number of columns: ");
  scanf("%d", &columns);

  //randomly generated indices for W
  wampusI = rand() % rows;
  wampusJ = rand() % columns;

  //dynamic memory allocation
  matrix = malloc(sizeof(char) * rows * columns);
  if (matrix == NULL){
    printf("error\n");
    exit(1);
  }

  //initializing matrix with manhattan distance values
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < columns; j++){
      int distance = abs(i-wampusI) + abs(j-wampusJ);
      char dist = distance + '0';
      matrix[i*columns + j] = dist;
    }
  }

  //placing W in proper index
  matrix[wampusI*columns + wampusJ] = 'W';

  //printing matrix
  for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", matrix[i * columns + j]);
        }
        printf("\n");
    }

    //free memory
    free(matrix);
    matrix = NULL;

  return 0;
}
