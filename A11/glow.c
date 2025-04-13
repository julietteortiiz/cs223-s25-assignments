#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

//globals
int w, h;

//dynamic array declaration
struct ppm_pixel *bright_earth;
struct ppm_pixel *blur_earth;
struct ppm_pixel *glow_earth;

//manages overflow
int clamp(int value)
{
  if (value < 0)
    return 0;
  if (value > 255)
    return 255;
  return value;
}

//creates blurred image
void calculate_pixel(int i, int j)
{
  int sum_red = 0;
  int sum_green = 0;
  int sum_blue = 0;
  for (int m = i - 2; m <= i + 2; m++)
  {
    for (int n = j - 2; n <= j + 2; n++)
    {
      struct ppm_pixel temp = bright_earth[m * w + n];
      sum_red += temp.red;
      sum_green += temp.green;
      sum_blue += temp.blue;
    }
  }
  blur_earth[i * w + j].red = clamp(sum_red / 25);
  blur_earth[i * w + j].green = clamp(sum_green / 25);
  blur_earth[i * w + j].blue = clamp(sum_blue / 25);
}

int main(int argc, char *argv[])
{
  //read in ppm file to create original image
  struct ppm_pixel *original_earth = read_ppm("earth-small.ppm", &w, &h);
  if (!original_earth)
  {
    printf("Error with read ppm\n");
    exit(1);
  }

  //create three other dynamic arrays to store transformed images
  bright_earth = malloc(sizeof(struct ppm_pixel) * w * h);
  if (!bright_earth)
  {
    printf("Error with bright allo\n");
    exit(1);
  }
  blur_earth = malloc(sizeof(struct ppm_pixel) * w * h);
  if (!blur_earth)
  {
    printf("Error with blur allo\n");
    exit(1);
  }
  glow_earth = malloc(sizeof(struct ppm_pixel) * w * h);
  if (!glow_earth)
  {
    printf("Error with glow allo\n");
    exit(1);
  }

  //saves new bright image into matrix
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      struct ppm_pixel pixel = original_earth[i * w + j];
      int brightness = (pixel.red + pixel.green + pixel.blue) / 3;
      if (brightness >= 200)
      {
        bright_earth[i * w + j].red = brightness;
        bright_earth[i * w + j].green = brightness;
        bright_earth[i * w + j].blue = brightness;
      }
      else
      {
        bright_earth[i * w + j].red = 0;
        bright_earth[i * w + j].green = 0;
        bright_earth[i * w + j].blue = 0;
      }
    }
  }

  //creates bright image
  write_ppm("bright.ppm", bright_earth, w, h);

  //saves blurred image into matrix w/ box 25
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      if (i <=2 || j <=2 || i >= (h-2) || j >= (w-2)){
        blur_earth[i * w + j] = bright_earth[i * w + j];
      } else {
        calculate_pixel(i,j);
      }
    }
  }

  //creates blurred image
  write_ppm("blur.ppm", blur_earth, w, h);

  //saves glowed image into matrix
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      glow_earth[i * w + j].red = clamp(original_earth[i * w + j].red + blur_earth[i * w + j].red);
      glow_earth[i * w + j].green = clamp(original_earth[i * w + j].green + blur_earth[i * w + j].green);
      glow_earth[i * w + j].blue = clamp(original_earth[i * w + j].blue + blur_earth[i * w + j].blue);
    }
  }

  //creates glow image
  write_ppm("glow.ppm", glow_earth, w, h);

  //fress allocated memory
  free(original_earth);
  free(bright_earth);
  free(blur_earth);
  free(glow_earth);

  return 0;
}
