#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])  
{
    if (argc != 2)
    {
        printf ("The argument number is not valid. Please try again.\n");
        return 1;
    }
    int k = atoi(argv[1]);
    printf("plaintext: ");
    string t = GetString();
    printf("ciphertext: ");
    for (int i = 0, n = strlen(t); i < n; i++)
    {            
        if (isalpha(t[i]))
            {
            if (isupper(t[i]))
                {
                printf("%c", 'A' + (t[i] - 'A' + k) % 26);
                }
            else if (islower(t[i]))
                {
                printf("%c", 'a' + (t[i] - 'a' + k) % 26);
                }
            }
        else
        {
         printf("%c", t[i]);   
        }
    }
    printf("\n");
    return 0;
}