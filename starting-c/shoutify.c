// shoutify.c
// Authors: Robbie Young
// Last modified: 10/01/22
// Use: For use in Carleton's CS208 2022 Course

#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("usage is %s inputfilename outputfilename\n", argv[0]);
        return 1;
    }
    FILE *inputfile = fopen(argv[1], "r"), *outputfile = fopen(argv[2], "w");

    if (inputfile == NULL) {
        printf("Could not open the inputfile %s\n", argv[1]);
        return 0;
    } else if (outputfile == NULL) {
        printf("Could not open the outputfile %s\n", argv[2]);
        return 0;
    }

    int c;
    while ((c = fgetc(inputfile)) != EOF) {
        if (96 < c && c < 123) {
            c = c - 32;
        }
        fputc(c, outputfile);
    }

    fclose(inputfile);
    fclose(outputfile);
    return 0;
}