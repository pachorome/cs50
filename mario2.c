#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int L; 
    int H;  
    int S; 
    int n;
   {
    do 
      {
       printf("Height: ");
       n = get_int();
       }
    while (n>23 || n<0);
       }
       for(L= 0; L <= n-1; L ++ ) 
          {
              {
                for ( S = n-2 ; S >= L ; S-- )
                   printf(" ");
              }
              {   
                for (H = 0 ; H <= L ;   H++)
                  printf("#"); 
              }   
            printf ("  ");
              {
                for (H = 0 ; H <= L; H++)
                printf("#");
              }
            printf ("\n");    
          }
       } 