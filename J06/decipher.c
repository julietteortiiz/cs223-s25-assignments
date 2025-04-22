#include <stdio.h>

int main()
{
    FILE* fp = fopen("message1", "rb");
    char c = fgetc(fp);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(fp);
    }
    return 0;
}
