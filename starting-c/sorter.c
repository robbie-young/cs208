// sorter.c
// Authors: Robbie Young
// Last modified: 10/01/22
// Use: For use in Carleton's CS208 2022 Course

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("usage: %s textfile\n", argv[0]);
        return 0;
    }
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Could not open %s\n", argv[1]);
        return 0;
    }

    char array[500][200];
    char line[200];
    int count = 0;
    while (fgets(line, 200, file)) {
        int i = 0;
        while (strcmp(array[i], line) < 0 && i < count) {
            i++;
        }
        
        if (strchr(line, '\n') == NULL) {
            line[strlen(line)] = '\n';
        }
        
        char temp[200];
        while (i < count) {
            strcpy(temp, array[i]);
            strcpy(array[i], line);
            strcpy(line, temp);
            i++;
        }

        count++;
        strcpy(array[i], line);
    }

    for (int i = 0; i < count; i++) {
        printf("%s", array[i]);
    }

    fclose(file);
    return 0;
}