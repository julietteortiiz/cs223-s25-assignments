/*----------------------------------------------
 * Author: Juliette Ortiz
 * Date: February 8, 2025
 * Program takes word and number as input and prints input word n times.
 * Malloc allocation to prevent system crashing.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *inputArray = NULL; //dynamic array in heap to keep track of input length
  char input[33]; //static array stores word input
  int len; //length of input word
  int count; //input number of times to count

  //input word
  printf("Enter a word: ");
  scanf("%s", input);
  len = strlen(input);

  //input count
  printf("Enter a count: ");
  scanf("%d", &count);
  
  //dynamic memory allocation and test
  inputArray = malloc(len * count + 1);
  if (inputArray == NULL){
    printf("Error: malloc failed! exiting. \n");
    exit(1);
  } 
  
  //printing output 
  printf("Your word is ");
  for (int i = 0; i < count; i++){
      printf("%s", input);
  }
  printf("\n");

  //memory allocation
  free(inputArray);
  inputArray = NULL;
  return 0;
}
