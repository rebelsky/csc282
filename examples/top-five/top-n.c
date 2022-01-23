/*
 ============================================================================
 Name        : top-n.c
 Author      : Moiz Yousufi
 Version     :
 Copyright   : Your copyright notice
 Description : Prints the five highest grades from HW2 in a CSV file
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DATA_FILE "grades.csv"
#define LINE_LENGTH 100
#define STRING_LENGTH 1024

int
main (int argc, char * argv[])
{
  // opens a file to read
  FILE * stream = fopen (DATA_FILE, "r");

  // checks to make sure file is not empty
  if (stream == NULL)
  {
    fprintf (stderr, "%s: Cannot open %s: %s\n",
             argv [0], DATA_FILE, strerror (errno));
    return -1;
  }

  int count; // initializes the counter for how many grades to sort
  scanf ("%d", &count);
  printf ("\n"); // separates input from output

  // array of strings
  char line [LINE_LENGTH] [STRING_LENGTH];
  int i; // loop variable

  // makes every string in line empty
  for (i = 0; i < LINE_LENGTH; ++i)
  {
    strcpy (line [i], "");
  } // end of for-loop

  char storeString [STRING_LENGTH];

  i = 0; // reset i

  // nested loop to collect data from .csv file
  while (fgets (storeString, STRING_LENGTH, stream))
  {
    // filter conditional to get only "HW2" data
    if(strstr (storeString, "HW2"))
    {
      int storeLength = strlen (storeString);
      int characterNum = 2;

      // inner loop to copy last few characters in filtered
      // .csv files to get the grades and copy to string
      for (int j = storeLength - 1; j > storeLength - 4; --j)
      {
          line [i] [characterNum--] = storeString [j];
      } // end of inner for-loop
      ++i; // iterates to the next string
        }
  } // end of outer while-loop

  int mainArr [count]; // array containing the grades data
  for (i = 0; i < count; ++i) // loop to initialize array
  {
    mainArr [i] = -1;
  } // end of for-loop

  // for-loop to convert and sort the grades in the array.
  for (i = 0; strcmp (line [i], ""); ++i)
  {
    int currNum = atoi (line [i]); // conversion from string to int

    for (int j = 0; j < count; ++j)
    {
      if (currNum > mainArr [j])
      {
        for (int k = count - 1; k > j; --k)
        {
          mainArr [k] = mainArr [k - 1];
        } // end inner-inner for-loop

        mainArr [j] = currNum;
        break;
      }
    } // end inner-outer for-loop
  } // end of outer for-loop

  // for-loop to print all values in mainArr
  for (i = 0; i < count; ++i)
  {
    if (mainArr[i] == -1)
    {
      // handling for when count > actual amount of grades
      printf("\n");
      printf("User input was higher than grades in HW2 Category\n");
      break;
    }

    printf ("%d ", mainArr [i]);
  }

  fclose (stream);

  return 0;
}

