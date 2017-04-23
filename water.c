#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int m;
    printf("Minutes: ");
    m = get_int();
    int b = m * 12;
    printf("Bottles: %i\n", b);
}