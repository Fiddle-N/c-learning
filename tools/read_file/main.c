#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define FILE_PATH "data/text_file.txt"

int main(void) {
    read_line_result read_line_res = read_line(FILE_PATH);
    if (read_line_res.status != 0) {
        return 1;
    }
    printf("%s", read_line_res.line);
    free(read_line_res.line);
}
