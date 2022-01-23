/* 
 * Some Student <student@grinnell.edu>
 *
 * TASK: Given a standard text file, convert all uppercase letters to
 * lowercase.
 *
 * Usage: To convert an input text file to all lowercase letters, pass the
 * name of the input file and the desired output file name as command-line
 * arguments.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    /* checks to see if there was a file argument passed */
    if (argc != 3) {
        fprintf(stderr, "usage: lower <input>.txt <output.txt>\n");
        exit(EXIT_FAILURE);
    }

    /* opens the input file for reading and checks for errors */
    FILE *in_fp;
    if (!(in_fp = fopen(argv[1], "r"))) {
        fprintf(stderr, "error: fopen failed\n");
        exit(EXIT_FAILURE);
    }

    /* opens output file for writing and checks for errors */
    FILE *out_fp;
    if (!(out_fp = fopen(argv[2], "w"))) {
        fprintf(stderr, "error: fopen failed\n");
        exit(EXIT_FAILURE);
    }

    /* 
     * iterates over the characters in the input file until it hits EOF,
     * writing the lower-case version of each character to the output file.
     *
     * note: tolower will leave non-alphabetical and lowercase letters
     * unchanged, so we don't have to check for either
     */
    char ch;
    while ((ch = getc(in_fp)) != EOF) {
        putc(tolower(ch), out_fp);
    }

    fclose(in_fp);
    fclose(out_fp);
}
