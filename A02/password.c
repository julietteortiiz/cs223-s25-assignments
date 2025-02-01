/***************************************************
 * Author: Juliette Ortiz
 * Date : February 1, 2025
 * 
 * program asks user for a word and provides a bad password by changing a few letters to 
 * non alphabet characters
 * 
 */
#include <stdio.h>
#include <string.h>

int main() {
    char input[20]; //static declaration of a char array (string) that can store max 19 letters
    int len; //keeps track of input word's length utilizing the string library

    void badPasswordAlg(char input[], int size); //function declaration
    
    printf("Enter a word:"); 
    scanf("%19s", input); //user inputs word
    len = strlen(input); //finds # of chars of input word
    badPasswordAlg(input, len); //calls function to generate bad password
    printf("Your bad password is: %s\n", input);

    return 0;
}

/*function creates a bad password by finding if the letters 'e', 'i', or 'a' exist 
in the string and then replaces them with non letter character */
void badPasswordAlg(char input[], int size){
        for (int i = 0; i < size; i ++){
            if (input[i] == 'e'){
                input[i] = '3';
            }
            else if (input[i] == 'i'){
                input[i] = '1';
                
            }
            else if (input[i] == 'a' ){
                input[i] = '@';
            }
        }
    }