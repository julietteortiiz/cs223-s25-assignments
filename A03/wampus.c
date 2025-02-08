/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

struct snack {
  char name[64];
  float price;
  int quantity;
};

int main() {
  struct snack *snackBar;
  int numberOfSnacks;

  printf("Enter number of snacks: ");
  scanf("%d", &numberOfSnacks);

  snackBar = malloc(sizeof(struct snack) * numberOfSnacks);
  
  for(int i = 0; i < numberOfSnacks; i++){
    printf("Enter a name: \n");
    scanf("%s", snackBar[i].name);
    printf("Enter a cost: \n");
    scanf("%f", &snackBar[i].price);
    printf("Enter a quantity: \n");
    scanf("%d", &snackBar[i].quantity);
  }

  printf("Welcome to Dynamic Donna's Snack Bar. \n \n");
  for (int i = 0; i < numberOfSnacks; i++){
    printf("%d)%s     cost:$%f    quantity:%d\n", i, snackBar[i].name, snackBar[i].price, snackBar[i].quantity);
  }



  return 0;
}
