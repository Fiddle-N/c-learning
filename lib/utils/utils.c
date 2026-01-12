#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


// returns the first line from the file as a pointer
// don't forget to free the pointer!
read_line_result read_line(const char *path) {
    FILE *fp;
    size_t bufsize = 1024;

    if (path == NULL) {
        return (read_line_result){READ_LINE_ERR_NULL_PATH, NULL};
    }

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

void read_line_free(read_line_result *res) {
    if (res == NULL) {
        return;
    }
    free(res->line);
    res->line = NULL;   // prevent double free error
}

void hello_world_lib(void) {
    printf("hello world from a library!\n");
}
