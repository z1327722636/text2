#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int mysh_pwd(char **args)
{
   char curpath[100];
   if(getcwd(curpath,sizeof(curpath)) != NULL){
    printf("%s\n",curpath);
   }else{
    perror("mysh_pwd");
   }
   return 1;
}
