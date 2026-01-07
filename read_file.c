#include <stdio.h>
#include <stdlib.h>

// returns the first line from the file as a pointer
// don't forget to free the pointer!
char *read_line(void) {
    FILE *fp = fopen("text_file.txt", "r");
    size_t bufsize = 1024;

    char *line_p = malloc(bufsize);
    if (line_p == NULL) {
        return NULL;
    }
    char *line = fgets(line_p, (int)bufsize, fp);
    if (line == NULL) {
        return NULL;
    }
    return line;
}
