#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (unlink(argv[1]) != 0) {
        perror("unlink");
        return 1;
    }

    printf("File deleted: %s\n", argv[1]);
    return 0;
}
