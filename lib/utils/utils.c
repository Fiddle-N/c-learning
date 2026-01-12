#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


// returns the first line from the file as a pointer
// don't forget to free the pointer!
read_line_result read_line(const char *path) {
    FILE *fp;
    size_t bufsize = 1024;

    fp = fopen(path, "r");
    if (fp == NULL) {
        return (read_line_result){READ_LINE_ERR_INVALID_FILE, NULL};
    }

    char *line_p = malloc(bufsize);
    if (line_p == NULL) {
        fclose(fp);
        return (read_line_result){READ_LINE_ERR_OOM, NULL};
    }
    fgets(line_p, (int)bufsize, fp);
    if (line_p == NULL) {
        free(line_p);
        fclose(fp);
        return (read_line_result){READ_LINE_ERR_READ, NULL};
    }
    fclose(fp);
    return (read_line_result){READ_LINE_OK, line_p};
}

void hello_world_lib(void) {
    printf("hello world from a library!\n");
}
