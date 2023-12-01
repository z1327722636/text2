#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int mysh_mkdir(char **args) {
    if (args[1] == NULL) {
         perror("参数错误,使用help命令查看帮助\n");
        return 1;
    }

    // 从第二个参数开始，依次创建目录
    for (int i = 1; args[i] != NULL; i++) {
        if (mkdir(args[i], 0777) != 0) {
             perror("创建失败,文件已经存在\n");
            return 1;
        }
    }

    return 1;
}

