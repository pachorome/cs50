#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)  
{
    string letters = GetString();
    int n = 0;
    int x, y;
    while (letters[n] == ' ')
    {
        n++;
    }
    printf("%c", toupper(letters[n]));
    for (x = n + 1, y = strlen(letters); x < y; x++)
    {
        while (letters[x] == ' ')
        {
            x++;
            if (x < y && letters[x] != ' ')
            {
                printf("%c", toupper(letters[x]));
            }
        }   
    }
    printf("\n");
}