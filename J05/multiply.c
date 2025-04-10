#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 4

// your code here

struct thread_data{
  int *M;
  int *u;
  int start_index;
  int end_index;
  int *result;
};

void *dot_product( void *threadData){
  struct thread_data *data = (struct thread_data * ) threadData;
      
  
  for (int i = data->start_index; i < data->end_index; i++){
    data->result[i] = 0;
    for(int j = 0; j < SIZE; j++){
      //printf("M:%d\n",data->M[i*SIZE + j]);
      //printf("u[j]:%d\n", data->u[j]);
      int value = data->M[i*SIZE + j];
      int r = value * data->u[j];
      data->result[i] += r;
    }
  }
  return (void*) NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int M[SIZE*SIZE];
  int u[SIZE];
  int result[SIZE];
  int result_threads[SIZE];
  
   
  for (int i = 0; i < SIZE; i++) {
    u[i] = rand() % 10 - 5; //initializes u
    result[i] = 0;
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int value = rand() % 10 - 5; //initializes
      M[i*SIZE + j] = value; 
      result[i] += value * u[j];
    }
  }

  printf("Result 1: [");
  for (int i = 0; i < SIZE; i++){
    printf("%d ", result[i]);
  }
  printf("\n");

  // TODO: Implement your thread solution here
  printf("Test with 4 threads\n");
  pthread_t threads[4];
  struct thread_data data[4];
  int subsize = SIZE/4;
  for (int i = 0; i < 4; i++){
    data[i].M = M;
    data[i].u = u;
    data[i].start_index = subsize*i;
    data[i].end_index = subsize*(i+1);
    data[i].result = result_threads;
    pthread_create(&threads[i], NULL, dot_product, &data[i]);
  }

  for (int i = 0; i < 4; i++){
    pthread_join(threads[i], NULL);
  }

 printf("Result Thread: [ ");
  for (int i = 0; i < SIZE; i++){
    printf("%d, ", result_threads[i]);
  }
  printf("]\n"); 




  int error = 0;
  for (int i = 0; i < SIZE; i++) {
    error += abs(result[i] - result_threads[i]);
  }
  printf("Error between ground truth and multithreaded version: %d\n", error);

  return 0;
}
