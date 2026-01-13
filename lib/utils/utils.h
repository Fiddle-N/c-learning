#pragma once

typedef enum {
    READ_FILE_OK,
    READ_FILE_ERR_NULL_PATH,
    READ_FILE_ERR_INVALID_FILE,
    READ_FILE_ERR_OOM,
    READ_FILE_ERR_READ,
} read_file_status;


typedef struct {
    read_file_status status;
    char **text;
} read_file_result;

read_file_result read_file(const char *path);
void read_file_free(read_file_result *res);
void hello_world_lib(void);
