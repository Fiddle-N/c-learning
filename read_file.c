#include <stdio.h>
#include <stdlib.h>


// returns the first line from the file as a pointer
// don't forget to free the pointer!
char *read_line(void) {
    FILE *fp;
    size_t bufsize = 1024;

    fp = fopen("text_file.txt", "r");
    if (fp == NULL) {
        return NULL;
    }

    char *line_p = malloc(bufsize);
    if (line_p == NULL) {
        fclose(fp);
        return NULL;
    }
    fgets(line_p, (int)bufsize, fp);
    if (line_p == NULL) {
        free(line_p);
        fclose(fp);
        return NULL;
    }
    fclose(fp);
    return line_p;
}
