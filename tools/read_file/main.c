#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define FILE_PATH "data/text_file.txt"

int main(void) {
    read_file_result read_file_res = read_file(FILE_PATH);
    if (read_file_res.status != 0) {
        return 1;
    }
    for (char **p = read_file_res.text; *p != NULL; p++) {
        printf("%s", *p);
    }
    read_file_free(&read_file_res);
}
