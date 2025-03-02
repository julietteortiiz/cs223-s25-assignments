// Author: Juliette Ortiz
// Date: March 1st, 2025
// Description: Program reads a file and prints out location of matching and unmatched braces


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*node pointer for easier variable declaration*/
typedef struct node *node_ptr;

/*node that holds the information for each bracket*/
struct node
{
  char type[2];
  int row;
  int column;
  node_ptr match;
  node_ptr next;
};

/* this list keeps track of the matched and unmatched brackets*/
void insertList(char type[2], int row, int column, node_ptr match, node_ptr *head)
{
  node_ptr tmp_cell = malloc(sizeof(struct node));
  if (tmp_cell == NULL)
  {
    printf("Error in insertList\n");
    exit(1);
  }
  /*copy information into new bracket node*/
  strcpy(tmp_cell->type, type);
  tmp_cell->row = row;
  tmp_cell->column = column;
  tmp_cell->match = match;

  /*inserts new bracket node at front of list and sets it to be the new head*/
  tmp_cell->next = *head;
  *head = tmp_cell;
}

/*iterates through list and frees all the nodes*/
void delete_list(node_ptr list)
{
  node_ptr temp;
  while (list != NULL)
  {
    temp = list;
    list = list->next;
    free(temp);
  }
}

/* variable fro keeping track of stack*/
typedef node_ptr STACK;

/*checks if stack is empy by checking stack head node and next in list*/
int is_empty(STACK S)
{
  return (S == NULL || S->next == NULL);
}

/*creates an empty stack*/
STACK create_stack(void)
{
  STACK S = (STACK)malloc(sizeof(struct node));
  if (S == NULL)
  {
    printf("Error in create_stack\n");
    exit(1);
  }
  S->next = NULL;
  return S;
}
/*creates new bracket node and pushes onto top of stack*/
void push(char type[2], int row, int column, STACK S)
{
  node_ptr tmp_cell = (node_ptr)malloc(sizeof(struct node));
  if (tmp_cell == NULL)
  {
    printf("Error in push\n");
    exit(1);
  }
  strcpy(tmp_cell->type, type);
  tmp_cell->row = row;
  tmp_cell->column = column;
  tmp_cell->next = S->next;
  S->next = tmp_cell;
}

/*pops and returns bracket node from top of stack*/
node_ptr pop(STACK S)
{
  if (is_empty(S))
  {
    printf("Error in pop: Stack is empty\n");
    exit(1);
  }

  node_ptr first_cell = S->next;
  S->next = first_cell->next;
  first_cell->next = NULL;
  return first_cell;
}

/*prints final list by determining matched and unmatched brackets*/
void printList(node_ptr head)
{
  if (head == NULL)
  {
    printf("List is empty\n");
    return;
  }

  node_ptr current = head;
  while (current != NULL)
  {
    if (current->match == NULL)
    {
      printf("Unmatched brace on Line %d and Column %d\n", current->row, current->column);
    }
    else
    {
      printf("Found matching braces: (%d,%d) -> (%d,%d)\n",
             current->match->row, current->match->column, current->row, current->column);
    }
    current = current->next;
  }
}

int main(int argc, char *argv[])
{
  int row = 0;
  int column = 0;
  STACK stack = create_stack();
  node_ptr head = NULL;

  FILE *filePointer = fopen(argv[1], "r");
  if (filePointer == NULL)
  {
    printf("Error: Unable to open file %s\n", argv[1]);
    return 1;
  }

  char line[100]; // for storing each line from file
  while (fgets(line, 100, filePointer) != NULL) 
  {
    row++; 
    column = 0;

    for (int i = 0; i < strlen(line); i++)
    {
      column++;
      /*if open bracket appears push to top of stack*/
      if (line[i] == '{')
      {
        push("{", row, column, stack);
      }
      /*if closed bracket appears first check if stack
      is empty to determine whether it is an unmatched closed bracket
      if not then insert it into a list with its matching open bracket
      */
      else if (line[i] == '}')
      {
        if (is_empty(stack))
        {
          insertList("}", row, column, NULL, &head);
        }
        else
        {
          node_ptr open_bracket = pop(stack);
          insertList("}", row, column, open_bracket, &head);
        }
      }
    }
  }

  /*have to check if there are any unmatched open brackets in the 
  stack. then just pop them from the stack and insert them into the list*/
  while (!is_empty(stack))
  {
    node_ptr unmatched = pop(stack);
    insertList("{", unmatched->row, unmatched->column, NULL, &head);
  }

  fclose(filePointer);
  printList(head);

  delete_list(head);
  free(stack); 

  return 0;
}
