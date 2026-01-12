#pragma once

typedef enum {
    READ_LINE_OK,
    READ_LINE_ERR_NULL_PATH,
    READ_LINE_ERR_INVALID_FILE,
    READ_LINE_ERR_OOM,
    READ_LINE_ERR_READ,
} read_line_status;


typedef struct {
    read_line_status status;
    char *line;
} read_line_result;

read_line_result read_line(const char *path);
void read_line_free(read_line_result *res);
void hello_world_lib(void);
