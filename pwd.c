#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        perror("getcwd");
        return 1;
    }

    printf("Current directory: %s\n", cwd);
    free(cwd);
    return 0;
}
