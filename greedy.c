 #include <stdio.h>
 #include "cs50.h"
 #include <math.h>

 int main(void)
 {
     float n;
     int c = 0;
     int t;

          do
     {
         printf("How much change is owed?\n");
         n = get_float();
     }
     while (n < 0);
     n *= 100.0;
     t = round (n);
     
     while (t >= 25)
     {
         c++;
         t -= 25;
     }

     while (t >= 10)
     {
         c++;
         t -= 10;
     }

     while (t >= 5)
     {
         c++;
         t -= 5;
     }

     while (t >= 1)
     {
         c++;
         t -= 1;
     }
     printf("%d\n", c);

     return 0;
 }