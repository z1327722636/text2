#include <stdio.h>
#include <stdlib.h>

int mysh_cat(char **args) {
    if (args[1] == NULL) {
        perror("参数错误,使用help命令查看帮助\n");
        return 1;
    }

    // 从第二个参数开始，依次打开文件并输出内容
    for (int i = 1; args[i] != NULL; i++) {
        FILE *file = fopen(args[i], "r");
        if (file == NULL) {
            perror("无法打开文件");
            return 1;
        }

        char ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }

        fclose(file);
    }

    return 1;
}
