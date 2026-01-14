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
    char **text_start = text;
    size_t line_no = 0;
    while (1) {
        char *line_pointer = calloc(line_size + 1, sizeof(char));           // add one for null terminator
        if (line_pointer == NULL) {
            // out of memory - unwind and close file
            *text = NULL;
            _read_file_free(text_start);
            fclose(fp);
            return (read_file_result){READ_FILE_ERR_OOM, NULL};
        }

        if (fgets(line_pointer, (int)line_size + 1, fp) == NULL) {
            if (ferror(fp)) {
                // read error
                free(line_pointer);
                *text = NULL;
                _read_file_free(text_start);
                fclose(fp);
                return (read_file_result){READ_FILE_ERR_READ, NULL};
            }
            // EOF
            assert(feof(fp));
            free(line_pointer);  // this is no longer needed
            break;
        }
        
        if (line_no >= file_size) {
            // gone over file line limit - unwind and close file
            free(line_pointer);
            *text = NULL;
            _read_file_free(text_start);
            fclose(fp);
            return (read_file_result){READ_FILE_ERR_FILE_TOO_LARGE, NULL};
        }

        // TODO check if line is too large
        // implementation currently splits long lines across multiple pointers
        *text = line_pointer;
        text++;
        line_no++;
    }
    *text = NULL;
    fclose(fp);
    return (read_file_result){READ_FILE_OK, text_start};
}


void hello_world_lib(void) {
    printf("hello world from a library!\n");
}
