#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

//thread data structure
struct thread_data
{
  int row_start;
  int row_end;
  int col;
  struct ppm_pixel *original;
  struct ppm_pixel *bright;
  struct ppm_pixel *blur;
  struct ppm_pixel *glow;
};

//manage overflow
int clamp(int value)
{
  if (value < 0)
    return 0;
  if (value > 255)
    return 255;
  return value;
};

void *operate(void *thread_data)
{
  struct thread_data *data = (struct thread_data *)thread_data;
  int w = data->col;
  int h = data->row_end;

  // get bright
  for (int i = data->row_start; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      struct ppm_pixel pixel = data->original[i * w + j];
      int brightness = (pixel.red + pixel.green + pixel.blue) / 3;
      if (brightness >= 200)
      {
        data->bright[i * w + j].red = brightness;
        data->bright[i * w + j].green = brightness;
        data->bright[i * w + j].blue = brightness;
      }
      else
      {
        data->bright[i * w + j].red = 0;
        data->bright[i * w + j].green = 0;
        data->bright[i * w + j].blue = 0;
      }
    }
  }

  // get blur
  for (int i = data->row_start; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      if (i <= 2 || j <= 2 || i >= (h - 2) || j >= (w - 2))
      {
        data->blur[i * w + j] = data->bright[i * w + j];
      }
      else
      {
        int sum_red = 0;
        int sum_green = 0;
        int sum_blue = 0;
        for (int m = i - 2; m <= i + 2; m++)
        {
          for (int n = j - 2; n <= j + 2; n++)
          {
            struct ppm_pixel temp = data->bright[m * w + n];
            sum_red += temp.red;
            sum_green += temp.green;
            sum_blue += temp.blue;
          }
        }
        data->blur[i * w + j].red = clamp(sum_red / 25);
        data->blur[i * w + j].green = clamp(sum_green / 25);
        data->blur[i * w + j].blue = clamp(sum_blue / 25);
      }
    }
  }

  // get glow
  for (int i = data->row_start; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      data->glow[i * w + j].red = clamp(data->original[i * w + j].red + data->blur[i * w + j].red);
      data->glow[i * w + j].green = clamp(data->original[i * w + j].green + data->blur[i * w + j].green);
      data->glow[i * w + j].blue = clamp(data->original[i * w + j].blue + data->blur[i * w + j].blue);
    }
  }
  return (void *)NULL;
};

int main(int argc, char *argv[])
{
  int N = 4;
  int threshold = 200;
  int blursize = 24;
  const char *filename = "earth-small.ppm";

  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1)
  {
    switch (opt)
    {
    case 'N':
      N = atoi(optarg);
      break;
    case 't':
      threshold = atof(optarg);
      break;
    case 'b':
      blursize = atof(optarg);
      break;
    case 'f':
      filename = optarg;
      break;
    case '?':
      printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]);
      break;
    }
  }

  //read in file and save width and height
  int w, h;
  struct ppm_pixel *original = read_ppm("earth-small.ppm", &w, &h);
  if (!original)
  {
    printf("Error with read ppm\n");
    exit(1);
  }

  //declare and allocate image matrices
  struct ppm_pixel *bright = malloc(sizeof(struct ppm_pixel) * w * h);
  if (!original)
  {
    printf("Error with read ppm\n");
    exit(1);
  }
  struct ppm_pixel *blur = malloc(sizeof(struct ppm_pixel) * w * h);
  if (!blur)
  {
    printf("Error with read ppm\n");
    exit(1);
  }
  struct ppm_pixel *glow = malloc(sizeof(struct ppm_pixel) * w * h);
  if (!glow)
  {
    printf("Error with read ppm\n");
    exit(1);
  }

  //creates 4 threads that create the new image parallel to each other
  pthread_t threads[4];
  struct thread_data data[4];
  int subsize = h / 4;
  for (int i = 0; i < 4; i++)
  {
    data[i].row_start = subsize * i;
    data[i].row_end = subsize * (i + 1);
    data[i].col = w;
    data[i].original = original;
    data[i].bright = bright;
    data[i].blur = blur;
    data[i].glow = glow;
    pthread_create(&threads[i], NULL, operate, &data[i]);
  }

  //wait for threads to finish
  for (int i = 0; i < 4; i++)
  {
    pthread_join(threads[i], NULL);
  }

  //create glow image
  write_ppm("glow.ppm", glow, w, h);

  //free allocated memory
  free(original);
  free(bright);
  free(blur);
  free(glow);
}
