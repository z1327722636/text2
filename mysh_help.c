#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int mysh_help(char **args){

 
 if (args[1] == NULL) {
        printf("Welcome to Help of My Shell !\n");
       printf("-------------------\n");
       printf("Command List as Following\n");
       printf("1)  查看命令使用 help [commond]\n"
        "2) 回显命令 echo\n"
        "3) 显示文件内容 cat\n"
        "4) 创建目录 mkdir\n"
        "5) 删除目录 rmdir \n"
        "6) 创建文件 touch\n"
        "7) 删除文件 rm\n"
        "8) 切换目录 cd\n"
        "9) 显示当前目录 pwd\n"
        "10) 文字统计 wc\n"
        "11) 结束程序 exit\n"
        "12)浏览目录和文件的各种属性 ls\n"
        "13) 输出重定向的使用 cdx\n");
    } else {
        char command_name[100]; // 存储命令帮助路径
        snprintf(command_name, sizeof(command_name), "help/%s.txt", args[1]);

        FILE *file = fopen(command_name, "r");
        if (file) {
            pid_t pid = fork();

            if (pid == 0) {
                // 子进程中执行分页器
                char *pager = "less"; // 使用 less 分页器
                char *pager_args[] = {pager, NULL};

                // 通过管道将帮助文档传递给分页器
                FILE *pipe = popen(pager, "w");
                char line[256];
                while (fgets(line, sizeof(line), file)) {
                    fputs(line, pipe);
                }
                fclose(file);
                pclose(pipe);

                // 子进程退出
                exit(0);
            } else if (pid > 0) {
                // 父进程等待子进程退出
                wait(NULL);
            } else {
                perror("fork");
            }
        } else {
            printf("No help available for '%s'\n", args[1]);
        }
    }

 return 1;
}


