/***************************************************
 * Author: Juliette Ortiz 
 * Date: February 1, 2025
 * 
 * This program gives the user three fruit options to purchase and allows them to purchase 1 item.
 * It then gives
 */
#include <stdio.h>
#include <string.h>

struct snackBar {
  char name[64];
  float cost;
  int quantity;
};

int main() {
  struct snackBar mango, strawberries, bananas; //three fruit options
  float money; //user's input, $
  int snackChoice; //the snack they want to buy

/*simple function that checks to see if the user can afford the snack, if there's sufficient quantity
and their total money after buying the snack*/
  void calculator(int x){
    if (x == 0){
        if (mango.quantity == 0){
            printf("There is no mango left\n");
        } 
        else {
        money = money - mango.cost;
        if (money < 0){
            printf("You can't afford it!\n");
        } else {
            printf("You bought Mango! \n You have $%f left\n", money);
        }
      } 
    } 
    else if (x == 1){
        if (strawberries.quantity == 0){
            printf("There are no strawberries left\n");
        } 
        else {
        money = money - strawberries.cost;
        if (money < 0){
            printf("You can't afford it!\n");
        } else {
            printf("You bought Strawberries! \n You have $%f left\n", money);
        }
      } 
    }
    else if (x == 2){
        if (bananas.quantity == 0){
            printf("There are no bananas left\n");
        } 
        else {
        money = money - bananas.cost;
        if (money < 0){
            printf("You can't afford it!\n");
        } 
        else {
            printf("You bought bananas! \n You have $%f left\n", money);
        }
      } 
    }
}

/*assigning name, cost, and quantity to fruit structs*/
  strcpy(mango.name, "Mango"); 
  strcpy(strawberries.name, "Strawberries");
  strcpy(bananas.name, "Bananas");

  mango.cost = 2.50;
  strawberries.cost = 1.0;
  bananas.cost = 0.5;

  mango.quantity = 5;
  strawberries.quantity = 10;
  bananas.quantity = 0;

  printf("How much money do you have?\n");
  scanf("%e", &money);
  
  printf("0) %s   Cost: $%f   Quantity: %i\n", mango.name, mango.cost, mango.quantity);
  printf("1) %s   Cost: $%f   Quantity: %i\n", strawberries.name, strawberries.cost, strawberries.quantity);
  printf("2) %s   Cost: $%f   Quantity: %i\n", bananas.name, bananas.cost, bananas.quantity);
  printf("What snack would you like? [0,1,2]\n");
  scanf("%d", &snackChoice);
  calculator(snackChoice); //passed snack choice 
  


  return 0;
}

