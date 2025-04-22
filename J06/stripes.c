#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "write_ppm.h"
#include <time.h>

struct thread_data {
  int starti;
  int endi;
  int width;
  int height;
  struct ppm_pixel color;
  struct ppm_pixel* image;
};

void *start(void* userdata) {
  struct thread_data* data = (struct thread_data*) userdata;
  int w = data->width;
  int h = data->endi;


  for (int i = data->starti; i < h; i++){
    for (int j = 0; j < w; j++){
      data->image[i * w + j].red = data->color.red;
      data->image[i * w + j].blue = data->color.blue;
      data->image[i * w + j].blue = data->color.red;
    }
    
  }

  return 0;
}

int main(int argc, char** argv) {

  if (argc != 2)
  {
    printf("usage: %s <num>\n", argv[0]);
    exit(0);
  }
  int N = strtol(argv[1], NULL, 10);


  int size = 1024;
  int subsize = 1024/N;
  struct ppm_pixel* image = malloc(sizeof(struct ppm_pixel) * size * size); //for image
  struct ppm_pixel* colors = malloc(sizeof(struct ppm_pixel) * N); //
  pthread_t* threads = malloc(sizeof(pthread_t) * N);
  struct thread_data* data = malloc(sizeof(struct thread_data) * N);


  for (int i = 0; i < N; i++) {
    data[i].starti = subsize * i;
    data[i].endi = subsize * (i + 1);
    data[i].width = size;
    data[i].height = size;
    data[i].color.red = (rand() % (250 - 0 + 1)) + 0;
    data[i].color.blue = (rand() % (250 - 0 + 1)) + 0;
    data[i].color.green = (rand() % (250 - 0 + 1)) + 0;
    data[i].image = image;
    pthread_create(&threads[i], NULL, start, &data[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  write_ppm("stripes.ppm", image, size, size);
}
