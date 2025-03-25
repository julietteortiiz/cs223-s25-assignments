/*----------------------------------------------
 * Author: Juliette Ortiz 
 * Date: February 20, 2025
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"


struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  struct ppm_pixel* array = malloc(sizeof(struct ppm_pixel) * 4 * 4);
  if(array == NULL){
    printf("Error: matrix cannot be created\n");
    exit(1);
  }

  //read in binary ppm file and access through filePointer
  FILE* filePointer = fopen(filename, "rb");
  //checking if filename is valid input
  if (filename == NULL){ 
    printf("Error: unable to open file %s\n", filename);
    exit(1);
  }

  char byte[30];
  fgets(byte, 24, filePointer);
  fgets(byte, 24, filePointer);
  fgets(byte, 24, filePointer);
  fgets(byte, 24, filePointer);
  fgets(byte, 24, filePointer);
  printf("%s", byte);

  // struct ppm_pixel* pixel;
  // pixel = malloc(sizeof(struct ppm_pixel));
  // fread(pixel, sizeof(struct ppm_pixel), 1, filePointer);
  // fread(pixel, sizeof(struct ppm_pixel), 1, filePointer);
  // printf("red:%d green:%d blue:%d\n", pixel->red, pixel->green, pixel->blue);
  void insert(struct ppm_pixel* pixel){

  }

  struct ppm_pixel* pixel = malloc(sizeof(struct ppm_pixel));
  fread(pixel, sizeof(struct ppm_pixel), 1, filePointer);
  while(fread(pixel, sizeof(struct ppm_pixel), 1, filePointer) != EOF){
    insert(pixel);
  }
  
  
  
  
  fclose(filePointer);

  free(array);  
  
  return NULL;
}



