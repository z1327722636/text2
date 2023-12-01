#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    if (chdir(argv[1]) != 0) {
        perror("chdir");
        return 1;
    }

    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        perror("getcwd");
        return 1;
    }

    printf("Current directory: %s\n", cwd);
    free(cwd);
    return 0;
}
