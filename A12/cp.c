// Author: Juliette Ortiz
// Date: April 18
// Description: Program infiatelky produces and consumes items using the same buffer. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define N 10 //size of buffer array

//globals
pthread_cond_t full = PTHREAD_COND_INITIALIZER; //for producer wait condition/signal
pthread_cond_t empty = PTHREAD_COND_INITIALIZER; //for consumer wait condition/signal
pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER; //for lock
int num_items = 0; //shared by p and c
int in = 0;//only accessed by producer
int out = 0; //only accessed by consumer
int buff[N]; //buffer array 

int produce_item() {
    return rand() % 10;
}

void consume_item(int item) {
  sleep(1);
    printf("Received item: %d\n", item);
}


void *producer_threads(void *id){
  int item;
  while(1){
    //create random int
    item = produce_item();  
    
    //mux is now locked and only one producer thread can access critical sections
    //in producer function AND consumer functions
    pthread_mutex_lock(&mux); 

    //if array is full:
    //1. make current producer thread sleep
    //2. unlock mux so consumer thread can start to empty buffer
    while(num_items >= N){
      pthread_cond_wait(&full, &mux);
    }
    //if buffer has space
    //1. add item
    //2. in++
    //3. numberitems++
    buff[in] = item;
    in = (in+1)%N;
    num_items++;

    //signals to consumer thread that buffer is no longer empty and items can be consumed
    pthread_cond_signal(&empty);
    //unlock critical sections
    pthread_mutex_unlock(&mux);
    //end of critical section
  }
};

void *consumer_threads(void *id){
  int item;
  while(1){
    //lock critical sections
    pthread_mutex_lock(&mux);
    //if buffer is empty
    while(num_items == 0){
      //wait until buffer has item before consuming
      pthread_cond_wait(&empty, &mux);
    }
    
    //1. get item at index out
    //2. update out
    //3. numberitems--
    item = buff[out];
    out = (out+1)%N;
    num_items--;

    //signal to producer threads that buffer is no longer full
    pthread_cond_signal(&full);
    //unlock critical sections
    pthread_mutex_unlock(&mux);
    //print item that was consumed
    consume_item(item);
  }
}


int main() {
  //declare thread variables
  int nthreads = 2; //number of threads
  long *producer_thread_ids;
  long *consumer_thread_ids;
  
  //allocate memory for array storing thread ids
  producer_thread_ids = malloc(nthreads* sizeof(pthread_t));
  if (producer_thread_ids == NULL){
    printf("Error w producer array\n");
    exit(1);
  }
  consumer_thread_ids = malloc(nthreads * sizeof(pthread_t));
  if (consumer_thread_ids == NULL){
    printf("Error w consumer array\n");
    exit(1);
  }

  //create thread ids and call thread functions
  for (int i = 0; i < nthreads; i++){
    producer_thread_ids[i] = i;
    consumer_thread_ids[i] = i;
    pthread_create(&producer_thread_ids[i], NULL, producer_threads, &producer_thread_ids[i]);
    pthread_create(&consumer_thread_ids[i], NULL, consumer_threads, &consumer_thread_ids[i]);
  }

  //join threads before continuing program
  for (int i = 0; i < nthreads; i++){
    pthread_join(producer_thread_ids[i], NULL);
    pthread_join(consumer_thread_ids[i], NULL);
  }

  //free memory
  free(producer_thread_ids);
  free(consumer_thread_ids);


  return 0;
}

