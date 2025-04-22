#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
    FILE* filePointer = fopen(filename, "rb");

    //reads P6
    char magic[3];
    fgets(magic, sizeof(magic), filePointer);  

    //Help from Isabella to read comments
    char line[128];
    while (fgets(line, sizeof(line), filePointer)) {
        if (line[0] == '#') continue;
        if (sscanf(line, "%d %d", w, h) == 2) break;
    }

    fgetc(filePointer); //consume max val (assuming 255)
    fgetc(filePointer); // consume newline after maxval

    //create array in heap
    struct ppm_pixel* array = malloc(sizeof(struct ppm_pixel) * (*w) * (*h));

    // read each pixel and insert into array
    fread(array, sizeof(struct ppm_pixel), (*w) * (*h), filePointer);

    fclose(filePointer);
    return array;
}
