#include "write_ppm.h"
#include <stdio.h>
#include <string.h>


void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
    FILE* filePointer = fopen(filename, "wb");
    if (!filePointer) {
        fprintf(stderr, "Error: Cannot open file %s for writing\n", filename);
        return;
    }

    //Write file header
    fprintf(filePointer, "P6\n%d %d\n255\n", w, h);
    
    // Write the pixel data
    if (fwrite(pixels, sizeof(struct ppm_pixel), w * h, filePointer) != (size_t)(w * h)) {
        fprintf(stderr, "Error: Failed to write pixel data\n");
    }

    fclose(filePointer);

}