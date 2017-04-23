/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 * CS50 
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/*
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
  //Set the length of the search
  int beg = 0;
  int fin = n - 1; 
  int mtd = (beg + fin) / 2;

  while (beg <= fin)
 {
    if (values[mtd] == value)
      return true;
    else if (value < values[mtd])
        {
          fin = mtd - 1;
          mtd = (beg + fin) / 2;
          // Set the middle of every search in left side
        }
    else if (value > values[mtd])
        {
          beg = mtd + 1;
          mtd = (beg + fin) / 2;
          // Set the middle in every search in right side
        }
      else 
        break;
  }
  return false;
}


/*
 * Sorts array of n values.
 */

void sort(int values[], int n)
{
    //Checking from left to right in a bubble sort
    
    for(int a = 1; a < n; a++)
    {
        int swip = values[a];
        int b = a-1;
        
        while((b >= 0) && (swip < values[b]))
        {
        // check if next number is lesser than current 
        // swap the numbers until the biggest is in the last position.  
            values[b+1] = values[b];
            b --;
        }
    
    values[b+1] = swip; 
    }
  
    return; 
}