#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


// returns the first two lines of a file
read_file_result read_file(const char *path) {
    FILE *fp;
    size_t line_size = 1024;
    // size_t line_num_size = 10000;

    if (path == NULL) {
        return (read_file_result){READ_FILE_ERR_NULL_PATH, NULL};
    }

    fp = fopen(path, "r");
    if (fp == NULL) {
        return (read_file_result){READ_FILE_ERR_INVALID_FILE, NULL};
    }

    // first line
    char *line_p = malloc(line_size);
    if (line_p == NULL) {
        fclose(fp);
        return (read_file_result){READ_FILE_ERR_OOM, NULL};
    }
    if (fgets(line_p, (int)line_size, fp) == NULL) {
        free(line_p);
        fclose(fp);
        return (read_file_result){READ_FILE_ERR_READ, NULL};
    }

    // second line
    char *line_p_2 = malloc(line_size);
    if (line_p_2 == NULL) {
        fclose(fp);
        return (read_file_result){READ_FILE_ERR_OOM, NULL};
    }
    if (fgets(line_p_2, (int)line_size, fp) == NULL) {
        free(line_p_2);
        fclose(fp);
        return (read_file_result){READ_FILE_ERR_READ, NULL};
    }

    // assemble two lines into outer pointer
    char **text = calloc(3, sizeof *text);    // two lines plus a null
    *text = line_p;
    text++;
    *text = line_p_2;
    text++;
    *text = NULL;
    text--;text--;  // walk back to original pointer location


    fclose(fp);
    return (read_file_result){READ_FILE_OK, text};
}

void read_file_free(read_file_result *res) {
    if (res == NULL) {
        return;
    }
    free(*(res->text));
    res->text++;
    free(*(res->text));
    // no need to autoincrement again to free null pointer
    res->text--;

    free(res->text);
    res->text = NULL;   // prevent double free error
}

void hello_world_lib(void) {
    printf("hello world from a library!\n");
}
