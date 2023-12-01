#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    if (mkdir(argv[1], 0755) != 0) {
        perror("mkdir");
        return 1;
    }

    printf("Directory created: %s\n", argv[1]);
    return 0;
}
