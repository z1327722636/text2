#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int mysh_cd(char **args)
{
    if(args[1] == NULL) 
    {
        perror("参数错误,使用help命令查看帮助\n");
        return 1;
    }
    else
    {
        if(chdir(args[1]) != 0)
        perror("error:路径未改变\n");
    }
    return 1;
}

