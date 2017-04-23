#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])  
{    
    if (argc != 2)
    {
        printf("The argument number is not valid. Please try again.\n");
        return 1;
    }
    else 
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Type only chars for the key.\n");
                return 1;
            }    
        }
    }
    string k = argv[1];
    int kLen = strlen(k);
    printf("plaintext: ");
    string p = GetString();
    printf("ciphertext: ");
    for (int a = 0, b = 0, n = strlen(p); a < n; a++)
    {            
        int code = tolower(k[b % kLen]) - 'a';
        if (isupper(p[a]))
        {
            printf("%c", 'A' + (p[a] - 'A' + code) % 26);
            b++;
        }
        else if (islower(p[a]))
        {
            printf("%c", 'a' + (p[a] - 'a' + code) % 26);
            b++;
        }
        else
        {
            printf("%c", p[a]);
        }
    }

    printf("\n");

    return 0;
}