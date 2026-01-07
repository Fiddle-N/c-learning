#include <stdio.h>
#include <stdlib.h>
#include "read_file.h"

int main(void) {
    char *line = read_line();
    if (line == NULL) {
        return 1;
    }
    printf("%s", line);
    free(line);
}
