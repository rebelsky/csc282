/*
 ============================================================================
 Name        : grades.c
 Author      : Student Name
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
#define STRING_LENGTH 256

 

int main(int argc, char* argv[])
{
    FILE* stream = fopen(DATA_FILE, "r");

 

    if(stream == NULL)
    {
        fprintf (stderr, "%s: Cannot open %s: %s\n",
                 argv[0], DATA_FILE, strerror(errno));
        return -1;
    }

 

    char line[LINE_LENGTH][STRING_LENGTH];
    int i;

 

    for(i = 0; i < LINE_LENGTH; ++i)
    {
        strcpy(line[i], "");
    }

 

    char storeString[STRING_LENGTH];

 

    i = 0;
    while(fgets(storeString, STRING_LENGTH, stream))
    {
        if(strstr(storeString, "HW2"))
        {
            int storeLength = strlen(storeString);
            int characterNum = 2;
            for(int j = storeLength - 1; j > storeLength - 4; --j)
            {
                line[i][characterNum--] = storeString[j];
            }
            ++i;
        }
    }

 

    int mainArr[5];
    for(i = 0; strcmp(line[i], "")/* line[i] != NULL */; ++i)
    {
        int currNum = atoi(line[i]);
        if(currNum > mainArr[0])
        {
            mainArr[4] = mainArr[3];
            mainArr[3] = mainArr[2];
            mainArr[2] = mainArr[1];
            mainArr[1] = mainArr[0];
            mainArr[0] = currNum;
            continue;
        }
        if(currNum > mainArr[1])
        {
            mainArr[4] = mainArr[3];
            mainArr[3] = mainArr[2];
            mainArr[2] = mainArr[1];
            mainArr[1] = currNum;
            continue;
        }
        if(currNum > mainArr[2])
        {
            mainArr[4] = mainArr[3];
            mainArr[3] = mainArr[2];
            mainArr[2] = currNum;
            continue;
        }
        if(currNum > mainArr[3])
        {
            mainArr[4] = mainArr[3];
            mainArr[3] = currNum;
            continue;
        }
        if(currNum > mainArr[4])
        {
            mainArr[4] = currNum;
            continue;
        }
    }

 

    for(i = 0; i < 5; ++i)
    {
        printf("%d ", mainArr[i]);
    }

 

    return 0;
} // end of program
