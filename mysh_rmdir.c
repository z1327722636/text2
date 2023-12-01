#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int mysh_rmdir(char **args) {
    if (args[1] == NULL) {
        perror("参数错误,使用help命令查看帮助\n");
        return 1;
    }

    // 从第二个参数开始，依次删除目录
    for (int i = 1; args[i] != NULL; i++) {
        if (rmdir(args[i]) != 0) {
            perror("mysh_rmdir");
            return 1;
        }
    }

    return 1;
}
