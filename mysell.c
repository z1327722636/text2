#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_INPUT_SIZE / 2 + 1];

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        // 读取用户输入
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0'; // 移除末尾的换行符

        // 解析用户输入为命令和参数
        int arg_count = 0;
        args[arg_count] = strtok(input, " ");
        while (args[arg_count] != NULL) {
            arg_count++;
            args[arg_count] = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        if (arg_count > 0) {
            // 检查是否退出 shell
            if (strcmp(args[0], "exit") == 0) {
                break;
            }

            // 执行命令
            pid_t pid = fork();
            if (pid == 0) {
                // 子进程
                execvp(args[0], args);
                perror("execvp");
                exit(1);
            } else if (pid > 0) {
                // 等待子进程结束
                wait(NULL);
            } else {
                perror("fork");
            }
        }
    }

    printf("Goodbye!\n");
    return 0;
}
