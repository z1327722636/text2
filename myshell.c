#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MYSH_TOK_DELIM " "
#define MYSH_BUFFER_SIZE 100

char username[MYSH_BUFFER_SIZE];
char hostname[MYSH_BUFFER_SIZE];
char curpath[MYSH_BUFFER_SIZE];


//获取指令
char * myshell_readline()
{
    char * line = NULL;
    ssize_t bufsize;
    //获取用户的输入指令
    getline(&line, &bufsize, stdin);

    // 去掉换行符
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
    return line;
}


//分解指令
char ** myshell_splitline(char * line)
{
    int buffer_size = MYSH_BUFFER_SIZE, position = 0;
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *token;

    token = strtok(line, MYSH_TOK_DELIM);
    while(token != NULL)
    {
        tokens[position++] = token;
        //传递NULL作为第一个参数，以表示它应该继续使用相同的字符串（`line`）来提取下一个令牌。
        token = strtok(NULL, MYSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

//执行命令
int mysh_without_execute(char **args)
{
    
    if (args[0] == NULL) {
    return 1;
} else if (strcmp(args[0], "help") == 0) {
    return mysh_help(args);
} else if (strcmp(args[0], "exit") == 0) {
    return mysh_exit(args);
} else if (strcmp(args[0], "ls") == 0) {
    return mysh_ls(args);
} else if (strcmp(args[0], "cat") == 0) {
    return mysh_cat(args);
} else if (strcmp(args[0], "echo") == 0) {
    return mysh_echo(args);
} else if (strcmp(args[0], "mkdir") == 0) {
    return mysh_mkdir(args);
} else if (strcmp(args[0], "rmdir") == 0) {
    return mysh_rmdir(args);
} else if (strcmp(args[0], "touch") == 0) {
    return mysh_touch(args);
} else if (strcmp(args[0], "rm") == 0) {
    return mysh_rm(args);
} else if (strcmp(args[0], "pwd") == 0) {
    return mysh_pwd(args);
} else if (strcmp(args[0], "wc") == 0) {
    return mysh_wc(args);
} else if (strcmp(args[0], "cd") == 0) {
    return mysh_cd(args);
} else {
    // 处理未知命令或错误
    perror("Unknown command\n");
    return 1;
}

}

int mysh_execute(char **args) {
    
    if (args[0] == NULL)
        return 1;

    int output_redirect = 0;
    char *output_filename = NULL;
    int i;
    char **args_a=malloc(MYSH_BUFFER_SIZE * sizeof(char *));
    
    FILE *output_file;

    // 检查是否有输出重定向符号 ">"
    for (i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            if (args[i + 1] == NULL) {
                perror("Missing output file name.\n");
                return 1;
            }
            output_redirect = i;//第几个分词是重定向符号
            for ( int j = 0; j < output_redirect; j++)
            {
                args_a[j] = args[j];
            }
            
            output_filename = args[i + 1]; // 下一个参数是输出文件名
            break;
        }
    }

    // 执行命令前检查输出重定向
    if (output_redirect != 0) {
        // 打开文件以供写入
        output_file = fopen(output_filename, "w");
        if (output_file == NULL) {
            perror("文件打开失败");
            return 1;
        }
        //保存原始终端的文件描述符
        int saved_stdout = dup(STDOUT_FILENO);
        // 使用 dup2 将标准输出重定向到文件
        dup2(fileno(output_file), STDOUT_FILENO);
        if(args_a[0][0] != '.'){
            mysh_without_execute(args_a);
        }else{
            
                pid_t child_pid;
                child_pid = fork();
                if (child_pid < 0) {
                    perror("Fork failed");
                    return 1;
                }

                if (child_pid == 0) {
                    // 子进程执行的代码
                    char *programName = args_a[0]; // 外部可执行文件的路径
                    char *const a[] = {programName, NULL}; // 参数数组，最后一个元素必须为 NULL

                    if (execvp(programName, a) == -1) {
                        perror("Execution failed");
                        exit(1); // 如果执行失败，通常会退出子进程
                    }
                } else {
                    // 父进程等待子进程完成
                    int status;
                    waitpid(child_pid, &status, 0);
                    if (WIFEXITED(status)) {
                        
                    }
                }
        }
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        fclose(output_file);
    }else{
        return mysh_without_execute(args);
    }

    return 1;
}

void myshell_loop()
{
    char *line;
    char **args;
    int status;
    printf("-----------------欢迎来到我的shell--------------\n ");
    printf("-------可以通过help命令获取帮助\n ");
    do
    {
        getcwd(curpath, sizeof(curpath));
        getlogin_r(username, sizeof(username));
        gethostname(hostname, sizeof(hostname));
        printf("\e[32;1m%s@%s\e[0m:%s$ ", username, hostname,curpath); // 显示为绿色

        line = myshell_readline();
        args = myshell_splitline(line);
        status = mysh_execute(args);

    } while (status);
    
}

int main(int argc, char *argv[])
{
    myshell_loop();
    return 0;
}