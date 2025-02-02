/***************************************************
 * Author: Juliette Ortiz
 * 
 * Date: February 1, 2025
 *
 * Program shifts letters of input word to create a cypher. 
 */
#include <stdio.h>
#include <string.h>

int main() {
  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  char input[50]; //input word
  int len; //len of input
  int shift; //magnitude of input shift number

  //finds index of input letter within the alphabet string
  int findIndex(char a){
    for (int i = 0; i < 26; i ++){
      if (a == alphabet[i]){
        return i;
      }   
      }
    }

  //shifts each letter in input by input shift
  void shiftIndex(int x){
    for (int i = 0; i < len; i ++){
      int originalAlphabetIndex = findIndex(input[i]);
      int newIndex = originalAlphabetIndex + x;
      char newLetter = alphabet[newIndex];
      input[i] = newLetter;
    }
  }

  printf("Enter a word: \n");
  scanf("%49s", input);
  len = strlen(input);
  printf("Enter a shift: \n");
  scanf("%d", &shift);
  shiftIndex(shift);
  printf("Your cypher is %s\n", input);

  return 0;
}
