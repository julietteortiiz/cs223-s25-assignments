#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1000

// your code here

struct thread_data {
  int *v;
  int *u;
  int start_index;
  int end_index;
  int result;
};

void *dot_product(void *threadData){
  struct thread_data *data = (struct thread_data *) threadData;
  for(int i = data->start_index; i < data->end_index;i++){
    //printf("U: %d\n", data->u[i]);
    //printf("V: %d\n",data->v[i]);
    int r = data->u[i] * data->v[i]; 
    data->result += r;
    //printf("Result: %d\n",data->result);
    
  }
  return (void*) NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int v[SIZE];
  int u[SIZE];
  int dotproduct = 0;
   
  


   
  //initializes vectors whil simultaneosly calculting dot product
  for (int i = 0; i < SIZE; i++) {
     v[i] = rand() % 1000 - 500;
     u[i] = rand() % 1000 - 500;
     dotproduct += u[i] * v[i];
   }
  printf("Ground truth dot product: %d\n", dotproduct);

  // TODO: Implement your thread solution here
  int thread_dotproduct = 0;
  printf("Test with 4 threads\n");
  pthread_t threads[4];
  struct thread_data data[4];
  int subsize = SIZE/4;
  for (int i = 0; i < 4; i++){
    data[i].v = v;
    data[i].u = u;
    data[i].start_index = subsize*i;
    data[i].end_index = subsize*(i+1);
    data[i].result = 0;
    pthread_create(&threads[i], NULL, dot_product, &data[i]);
  }

  for (int i = 0; i < 4; i++){
    pthread_join(threads[i], NULL);
    thread_dotproduct += data[i].result;
  }


  printf("Answer with threads: %d\n", thread_dotproduct);

  return 0;
}
