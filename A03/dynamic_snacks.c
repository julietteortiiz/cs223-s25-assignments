/*----------------------------------------------
 * Author: Juliette Ortiz
 * Date: February 8, 2025
 * Creates an array storing snack informationas given by user.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

struct snack {
  char name[64];
  float price;
  int quantity;
};

int main() {
  struct snack *snackBar; //pointer to a struct snack
  int numberOfSnacks;

  printf("Enter number of snacks: ");
  scanf("%d", &numberOfSnacks);

  //dynamic array of snacks in snack bar
  snackBar = malloc(sizeof(struct snack) * numberOfSnacks);
  
  //allows for user to give snack information then stores them in array
  for(int i = 0; i < numberOfSnacks; i++){
    printf("Enter a name: ");
    scanf("%s", snackBar[i].name);
    printf("Enter a cost: ");
    scanf("%f", &snackBar[i].price);
    printf("Enter a quantity: ");
    scanf("%d", &snackBar[i].quantity);
  }

  printf("Welcome to Dynamic Donna's Snack Bar. \n \n");
  for (int i = 0; i < numberOfSnacks; i++){
    printf("%d)%s     cost:$%f    quantity:%d\n", i, snackBar[i].name, snackBar[i].price, snackBar[i].quantity);
  }



  return 0;
}
