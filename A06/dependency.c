#include <stdio.h>
#include "tree.h"

int main(int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
  {
    FILE *filePointer = fopen(argv[i], "r");
    if (filePointer == NULL)
    {
      printf("Error: Unable to open file %s\n", argv[1]);
      return 1;
    }
    char line[100]; // for storing each line from file
    while (fgets(line, 100, filePointer) != NULL)
    {
      printf("%s", line);
    }

    fclose(filePointer);
  }

  return 0;
}
