/***************************************************
 * mathgame.c
 * Author: Juliette Ortiz
 * Implements a math game by 
 * 1. asking user for the number of rounds they'd like to play 2
 * 2. asking math addition problems by randomly generating numbers
 * 3. checking whether the user's answer was correct or incorrect
 * 4. printing out the number of correct answers
 */

#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("Welcome to Math Game!\n");
    printf("How many rounds do you want to play?");
    
    int response = 0;
    scanf("%d", &response);
    
    int correctAnswers = 0;
    
    for (int i = 0; i < response; i++){
        int x = rand();
        int y = rand();
        x /= 100000000;
        y /= 100000000;
        printf("%d + %d = ?\n", x, y);
        
        int answer = 0;
        scanf("%d", &answer);
        if (answer == (x + y)){
            correctAnswers ++;
            printf("Correct!\n");
        } else {
            printf("Incorrect :(\n");
        }
    }
    
    printf("You answered %d/%d correctly.\n", correctAnswers, response);
    

    return 0;
}
