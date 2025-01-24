/***************************************************
 * mathgame.c
 * Author: Juliette Ortiz
 * Implements a math game by 
 * 1. asking user for the number of rounds they'd like to play 2
 * 2. asking math addition problems by randomly generating numbers
 * 3. checking whether the user's answer was correct or incorrect
 * 4. printing out the number of correct answers
 * 
 * @version: January 24, 2024
 */

#include <stdio.h>
#include <stdlib.h> //for rand()


int main() {
    printf("Welcome to Math Game!\n");
    printf("How many rounds do you want to play?");
    
    //user input, # of rounds
    int response = 0; 
    scanf("%d", &response);
    
    //keeps track of the # of correct answers by the user
    int correctAnswers = 0;
    
    for (int i = 0; i < response; i++){
        /* x and y are randomly generated #s used in the
        prompted math question. They're then reduced to 
        simplify the question. 
        */
        int x = rand(); 
        int y = rand();
        x /= 100000000; 
        y /= 100000000;
        printf("%d + %d = ?\n", x, y);
        
        //stores the user's guess answer to the problem
        int answer = 0;
        scanf("%d", &answer);
        if (answer == (x + y)){
            correctAnswers ++;
            printf("Correct!\n");
        } 
        else {
            printf("Incorrect :(\n");
        }
    }
    
    printf("You answered %d/%d correctly.\n", correctAnswers, response);
    
    return 0;
}
