#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*find function recursively searches through tree by comparing name to data
stored at each node*/
struct tree_node *find(const char *name, struct tree_node *root)
{
  /*If there's nothing in root, then return NULL*/
  if (root == NULL)
  {
    return NULL;
  }
  /*checks if search should go left or right of root*/
  if (strcmp(name, root->data.name) < 0)
  {
    return (find(name, root->left));
  }
  else if (strcmp(name, root->data.name) > 0)
  {
    return (find(name, root->right));
  }
  /*item has been found, returns root node*/
  else
  {
    return root;
  }
}

/*Insert method uses a recursive approach where each tree node
can be defined as the root. Tree is sorted upon insertion which
enhances search and traversal methods*/
struct tree_node *insert(const char *name, struct tree_node *root)
{

  /*If root is empty, create and return a one tree node*/
  if (root == NULL)
  {
    root = malloc(sizeof(struct tree_node));
    if (root == NULL)
    {
      printf("Out of Space!\n");
      exit(1);
    }
    else
    {
      strcpy(root->data.name, name);
      root->left = root->right = NULL;
    }
  }
  /*If root is not empty then proceed to recursively search and
  place in correct position within tree. Utilizes built in
  string comparison method.

  1. If strcmp(str1, str2) > 0 then str1 is greater
  2. If strcmp(str1,str2) < 0 then str2 is greater
  3. If strcmp(str1,str2) = 0 then str1 and str2 are equal
  (Credit: GeeksforGeeks)

  */
  else if (strcmp(name, root->data.name) < 0)
  {
    root->left = insert(name, root->left);
  }
  else if (strcmp(name, root->data.name) > 0)
  {
    root->right = insert(name, root->right);
  }
  return root;
}

/*CLear method recursively clears left subtree then right subtree*/
void clear(struct tree_node *root)
{
  if (root == NULL){
    return;
  } else {
    clear(root->left); //recursive call on left
    clear(root->right); //recursive call on right
    free(root); //free current
  }
}

/*Declarations to avoid bug issues*/
void printLeft(struct tree_node *root, int indent);
void printRight(struct tree_node*root, int indent);

/*Prints left tree nodes*/
void printLeft(struct tree_node *root, int indent){
  if (root == NULL){
    return;
  } else {
    for (int i = 0; i < indent; i++){
      printf(" ");
    }
    printf("l:%s\n", root->data.name);

    printLeft(root->left, indent++);
    printRight(root->right, indent++);
  }  
}

/*Prints right tree nodes*/
void printRight(struct tree_node *root, int indent){
  if (root == NULL){
    return;
  } else {
    for (int i = 0; i < indent; i++){
      printf(" ");
    }
    printf("r:%s\n", root->data.name);

    printLeft(root->left, indent++);
    printRight(root->right, indent++);
  }  
}

/*Print method pre-order traversal*/
void print(struct tree_node *root, int indent)
{
  if (root == NULL)
  {
    return;
  }
  else
  {
    printf("%s\n", root->data.name);
    
    printLeft(root->left, indent++); 
    printRight(root->right, indent++);
  }

}




/*PrintSorted method is a recursive in-order BST traversal*/
void printSorted(struct tree_node *root)
{
  if (root != NULL)
  {
    printSorted(root->left);
    printf("%s\n", root->data.name);
    printSorted(root->right);
  }
}
