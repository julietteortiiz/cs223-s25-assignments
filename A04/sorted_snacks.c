#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct snack{
    char name[64];
    double cost;
    int quantity;
    struct snack* next;
};

void freeList(struct snack* head){
  struct snack* prev = head;
  struct snack* current = head->next;
  while (current-> next != NULL){
      free(prev);
      prev = current;
      current = current->next;
  }
  free(current);
  head = NULL;
};

//passes back length of list not including head
int lengthOf(struct snack* head){
  int len = 0;
  struct snack* current = head->next;
  while ( current != NULL){
    len++;
    current = current -> next;
  }
  return len;
};

void printList(struct snack* head){
    printf("Welcome to Sorted Sally's Snack Bar.\n\n");
    struct snack* current = head -> next;
    int i = 0;
    while(current != NULL){
        printf("%d) %s\t Cost:$%.2f\t Quantity:%d\n",i, current->name, current->cost, current->quantity);
        i++;
        current = current -> next;
    }
    printf("\n");
};

void printNames(struct snack *head){
  struct snack* current = head;
  while(current != NULL){
    printf("%s ->", current->name);
    current = current->next;
  }
  printf("\n");
};
//splits linked list into two halves, returning the pointer to the head of the second half
//if list has an odd amount of items then the first half will have +1 item
struct snack* split(struct snack* head){
  //printf("Split!\n");
  //case if there is only 1 item that is asked to be split
  if (head->next == NULL){
    return NULL;
  }
    int len = lengthOf(head)/2;
    struct snack* current = head;
    for (int i=0; i < len; i++){
        current = current->next;
    }
    struct snack* secondHalf = current->next; //creates pointer to second half
    current->next = NULL; //seperates first half from second half
    return secondHalf; 
}

//accepts the values for the new snack and the head node as inputs
//creates and inserts new node at begining of list st 
// head -> oldNode -> NULL + newNode = head -> newNode -> oldNode -> NULL
void insertFront(char name[], double cost, int quantity, struct snack* headPtr){
        struct snack* newSnackPtr = malloc(sizeof(struct snack)); //creates new snack node
        if (newSnackPtr == NULL){
            printf("Error allocating memory :(\n");
            exit(1);
        } if (headPtr->next == NULL){ //case if the head sentinal is the only node in the list
            headPtr->next = newSnackPtr;
            newSnackPtr->next = NULL;
        } else { //case if there is already an existing node that head sentinal points to
            newSnackPtr->next = headPtr->next;
            headPtr->next = newSnackPtr;
        }
        //assigns new node input values for snack
        strcpy((*newSnackPtr).name, name); 
        newSnackPtr->cost = cost;
        newSnackPtr->quantity = quantity;
        
}

//swaps the positions of two nodes by reassigning pointers
void swap(struct snack* snackA, struct snack* snackB){
    struct snack* temp = snackA->next;
    snackA->next = snackB->next;
    snackB->next = temp;
};

//currently compares quantity
int compare(struct snack* snackA, struct snack* snackB){ 
  if (snackA->quantity >= snackB->quantity){
    return 1;
  } else {
    return -1;
  }
};

struct snack* merge(struct snack* firstHalf, struct snack* secondHalf){
  printf("Merge!");
  if (secondHalf == NULL){
    return firstHalf;
  }
  struct snack* currentFirst = firstHalf;
  struct snack* currentSecond = secondHalf;
  while (currentFirst != NULL && currentSecond != NULL){
    int greater = compare(currentFirst, currentSecond);
    
    //case if currentFirst goes before currentsecond
    if (greater == 1 ){
      currentSecond = currentSecond->next;
    } else {
      swap(currentFirst,currentSecond);
      currentSecond = currentFirst;
      currentFirst = currentFirst -> next;
    }
    currentFirst->next = currentSecond;
  }
  return currentFirst;
};


//recursive mergeSort function that utilizes the split() and merge() functions
//returns a pointer to the begining of the sorted list 
struct snack* mergeSort(struct snack* head){
  if (split(head) == NULL){
    printf("split(head) is null\n");
    return head;
  }
  
  struct snack* firstHalf = head;
  printf("First half:");
  printNames(firstHalf);
  struct snack* secondHalf = split(head);
  
  struct snack* sorted1 = mergeSort(firstHalf);
  struct snack* sorted2 = mergeSort(secondHalf);
  
  return merge(sorted1, sorted2);
};


int main() {
    struct snack* head = malloc(sizeof(struct snack));
    head->next = NULL;
    
    insertFront("Chips", 1.50, 2, head);
    insertFront("Raisins", 4.15, 5, head);
    insertFront("Bananas", 0.50, 10, head);
    
    
    //printf("Size:%d snacks\n", lengthOf(head));
    //printList(head);
    //printf("Old: ");
    printNames(head);
    //struct snack* newList = mergeSort(head->next);
    struct snack* secondHalf = split(head);
    printNames(head);
    printNames(secondHalf);
    //printNames(secondHalf);
    //printf("First half merge Sort: ");
    //printNames(mergeSort(head));
    //printf("Second Half merge sort: ");
    //printNames(mergeSort(secondHalf));
    printf("split on head");
    printNames(split(head));

    //printf("New:");
    //printNames(newList);
    //printList(newList);
    
    return 0;
}