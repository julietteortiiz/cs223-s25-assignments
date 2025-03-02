#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bracket* stack = NULL;
struct matchingBrackets* matchedBracketsList = NULL;
struct bracket {
  char type[8]; //Will be defined as Open or Close
  int row;
  int column;
  struct bracket* next;
};
struct matchingBrackets{
  struct bracket* open;
  struct bracket* close;
  struct matchingBrackets* next;
};
void push(struct bracket* bracket){
  if (stack == NULL){
    stack = bracket;
  } else {
    struct bracket* current = stack;
    while(current->next != NULL){
      current = current->next;
    }
    current->next = bracket;
  }
};
struct bracket* pop(){
  struct bracket* current = stack;

  if (stack == NULL){
    printf("Error: stack is empty. Cannot be popped\n");
    exit(1);
  } if (stack->next == NULL){
    current = stack;
    stack = NULL;
    return current;
  } else {
    struct bracket* prev;
    while(current->next != NULL){
      prev = current;
      current = current->next;
    }
    prev->next = NULL;
    return current;
  }
};

void printStack(){
  if (stack == NULL){
    printf("Stack is empty\n");
  }
  struct bracket* current = stack;
  while (current != NULL){
    printf("%s at (%d,%d)\n", current->type, current->row, current->column);
    current = current->next;
  }
};

void printList(){
  if (matchedBracketsList == NULL){
    printf("Matched bracket list is empty\n");
  }
  struct matchingBrackets* current = matchedBracketsList;
  while ( current != NULL){
    if(current->open == NULL || current->close == NULL){

    }
    current = current->next;
  }
};

void insert(struct bracket* newBracket){
  if (matchedBracketsList == NULL){
    matchedBracketsList = newBracket;
  } else {
    struct matchingBrackets* current = matchedBracketsList;
    while(current->next != NULL){
      current = current->next;
    }
    current->next = newBracket;
  }
};

int main(int argc, char *fileName[]){
  int row = 0; //keeps track of row as file is iterated through
  int column = 0; //keeps track of column as line is iterated through
  
  FILE* filePointer = fopen(fileName[1], "r");
  if(filePointer == NULL){
    printf("Error: unable to open file %s\n", fileName[1]);
    exit(1);
  }

  char line[100]; //for storing each line from file
  
  while(fgets(line, 100, filePointer)){
    row++; 
    column = 0;
    
    //iterate through each character in line
    for (int i = 0; i < strlen(line); i++){
      column++;
      if (line[i] == '{' || line[i] == '}'){ 
        
        //create a bracket struct to store information about new bracket
        struct bracket* newBracket  = malloc(sizeof(struct bracket));
        if (newBracket == NULL){
          printf("Malloc Error making bracket");
          exit(1);
        }

        //assign row, column, and next values
        newBracket->row = row; 
        newBracket->column = column;
        newBracket->next = NULL;
        
        //if open bracket, push onto stack
        if (line[i] == '{'){
          
          //assign newBracket as open bracket type
          strcpy(newBracket->type, "Open");
          
          //push onto stack
          push(newBracket);
        } 
        
        //if closed bracket, 
        else if(line[i] == '}'){
          //assign newBracket as closed bracket type
          strcpy(newBracket->type, "Close"); 

          //create a newMatch that will pair each open and closed bracket
          struct matchingBrackets* newMatch = malloc(sizeof(struct matchingBrackets));
          if (newMatch == NULL){
            printf("Error: couldnt create new match\n");
            exit(1);
          }

          /*if stack is empty then the new closed bracket doesn't have 
          an open pair, thus open = NULL for newMatch. 
          */
          if(stack == NULL){
            newMatch->open = NULL;
            newMatch->close = newBracket;
            insert(newMatch);
          } 
          
          else {
            struct bracket* openBracket = pop();
            newMatch->open = openBracket;
            newMatch->close = newBracket;
            insert(newMatch);
            }
          }
        }
      }
    }
  }
  //create free for both lists
  printStack();
  return 0;
}

