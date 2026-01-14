#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"


static void _read_file_free(char **text) {
    if (text == NULL) {
        return;
    }
    for (char **text_p = text; *text_p != NULL; text_p++) {
        free(*text_p);
    }
    free(text);
}


void read_file_free(read_file_result *res) {
    if (res == NULL) {
        return;
    }
    _read_file_free(res->text);
    res->text = NULL;      // prevent double free error
}


read_file_result read_file(const char *path) {   
    if (path == NULL) {
        return (read_file_result){READ_FILE_ERR_NULL_PATH, NULL};
    }

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        return (read_file_result){READ_FILE_ERR_INVALID_FILE, NULL};
    }

    size_t file_size = 10000;
    char **text = calloc(file_size + 1, sizeof(char *));       // add one for null terminator
    if (text == NULL) {
        fclose(fp);
        return (read_file_result){READ_FILE_ERR_OOM, NULL};
    }

    size_t line_size = 1024;
    char **text_cursor = text;
    size_t line_no = 0;
    char *line_p = NULL;
    read_file_status status = READ_FILE_ERR_UNEXPECTED;
    while (1) {
        line_p = calloc(line_size + 1, sizeof(char));           // add one for null terminator
        if (line_p == NULL) {
            // out of memory - unwind and close file
            status = READ_FILE_ERR_OOM;
            break;
        }

        if ((fgets(line_p, (int)line_size + 1, fp)) == NULL) {
            if (ferror(fp)) {
                // read error
                status = READ_FILE_ERR_READ;
                break;
            }
            // EOF
            assert(feof(fp));
            status = READ_FILE_OK;
            break;
        }
        
        if (line_no >= file_size) {
            // gone over file line limit - unwind and close file
            status = READ_FILE_ERR_FILE_TOO_LARGE;
            break;
        }

        // TODO check if line is too large
        // implementation currently splits long lines across multiple pointers
        *text_cursor = line_p;
        text_cursor++;
        line_no++;
    }

    // cleanup
    free(line_p);
    *text_cursor = NULL;
    fclose(fp);
    if (status != READ_FILE_OK) {
        _read_file_free(text);
        text = NULL;
    }

    return (read_file_result){status, text};
}


void hello_world_lib(void) {
    printf("hello world from a library!\n");
}
