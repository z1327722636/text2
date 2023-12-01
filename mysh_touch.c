#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <unistd.h>

int mysh_touch(char **args) {
    if (args[1] == NULL) {
        perror("参数错误,使用help命令查看帮助\n");
        return 1;
    }

// 从第二个参数开始，依次创建文件
    for (int i = 1; args[i] != NULL; i++) {
        int fd = open(args[i], O_CREAT | O_WRONLY, 0666);
        if (fd == -1) {
            perror("mysh_touch");
            return 1;
        }
        close(fd);
        
    }
    
    return 1;
}

