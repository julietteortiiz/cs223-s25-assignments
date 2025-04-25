// Author: Juliette Ortiz
//Date: April 25, 2025
// Malloc and free implementation using first fit strategy in attempt to optimize
// speed and amount of memory used.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size; //size of memory allocated from sbrk
  int used; //amount currently in use
  struct chunk *next; 
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  if (size == 0){
    return NULL;
  }
  struct chunk *next = flist;
  struct chunk *prev = NULL;

  //check freed list if there can be memory reused
  while (next != NULL){ //iterate through entirety of free list
  //check if the current freed memory block has a greater size than that being requested by the user
    if (next->size >= size){
      //if yes take that block and reset the pointers of freed list
      if (prev != NULL){
        prev->next = next->next;
      } else {
        flist = next -> next;
      }
      next->used = size; //save the amount that's actually being used
      return (void*)(next + 1); //return that memory block (what next was pointing to)
    } else {
      prev = next;
      next = next -> next;
    }
  }
  void *memory = sbrk(size + sizeof(struct chunk));
  if(memory == (void *) - 1){
    return NULL;
  } else {
    struct chunk *cnk = (struct chunk*) memory;
    cnk->size = size;
    cnk->used = size;
    return (void*)(cnk+1);
  }
}

void free(void *memory) {
  if (memory != NULL){
    struct chunk *cnk = (struct chunk*)((struct chunk *)memory - 1);
    cnk->next = flist;
    flist = cnk;
  }
  return;
}
