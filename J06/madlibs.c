#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 32

int main()
{
    int boolean;
    int numAdjectives;
    char true[20];

    printf("Boolean: ");
    scanf("%d", &boolean);
    printf("Number: \n");
    scanf("%d", &numAdjectives);

    if (boolean == 1)
    {
        strcpy(true, "true");
    }
    else
    {
        strcpy(true, "false");
    }

    char **pointers = malloc(sizeof(char *) * numAdjectives);

    for (int i = 0; i < numAdjectives; i++)
    {
        char str[32];
        char *string = malloc(32);
        printf("Adjective: ");
        scanf("%s", str);
        strcpy(string, str);
        pointers[i] = string;
    }

    printf("You are the most ");

    for (int i = (numAdjectives - 1); i != -1; i--)
    {
        printf("%s", pointers[i]);
        printf(",");
    }

    printf(" person that I know and you know its %s\n", true);

    for (int i = 0; i < numAdjectives; i++)
    {
        free(pointers[i]); 
    }
    free(pointers); // Free the array of pointers

    return 0;
}
