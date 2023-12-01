#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

#define ls_l 1
#define ls_a 2

void list_files(const char *path, int ls_option[]) {
    //表示目录
    DIR *dir;
    //表示目录中的条目
    struct dirent *entry;
    //存储文件的详细信息
    struct stat file_info;

    if ((dir = opendir(path)) == NULL) {
        perror("路径不存在\n");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
       if (entry->d_name[0] == '.'   ) {
            if (  ls_option[ls_a] == 0 ) {
            continue; // 隐藏文件，如果不显示详情则跳过
            }
        }

        char full_path[512];//包含目录路径和文件名
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        //lstat 函数用于获取文件的详细信息，并将结果存储在 file_info 结构中
        if (lstat(full_path, &file_info) == -1) {
            perror("lstat");
            continue;
        }
        //通过标志判断是否有 -l参数
        if ( ls_option[ls_l] == 1) {
            // 显示详细信息
            char permissions[11];
            permissions[10] = '\0';
            mode_to_letters(file_info.st_mode, permissions);

            struct passwd *user_info = getpwuid(file_info.st_uid);
            struct group *group_info = getgrgid(file_info.st_gid);

            char time_buffer[80];
            strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M", localtime(&file_info.st_mtime));

            printf("%s %2ld %s %s %5ld %s %s\n", permissions, (long)file_info.st_nlink,
                user_info->pw_name, group_info->gr_name, (long)file_info.st_size, time_buffer, entry->d_name);
        } else {
            printf("%s\t", entry->d_name);
        }
    }

    closedir(dir);
     printf("\n");
}

//将文件的的权限转换为可读的字符串表示
void mode_to_letters(mode_t mode, char str[]) {
    strcpy(str, "----------");

    if (S_ISDIR(mode)) str[0] = 'd';  // 目录
    if (S_ISCHR(mode)) str[0] = 'c';  // 字符设备
    if (S_ISBLK(mode)) str[0] = 'b';  // 块设备

    if (mode & S_IRUSR) str[1] = 'r'; // 用户读权限
    if (mode & S_IWUSR) str[2] = 'w'; // 用户写权限
    if (mode & S_IXUSR) str[3] = 'x'; // 用户执行权限

    if (mode & S_IRGRP) str[4] = 'r'; // 组读权限
    if (mode & S_IWGRP) str[5] = 'w'; // 组写权限
    if (mode & S_IXGRP) str[6] = 'x'; // 组执行权限

    if (mode & S_IROTH) str[7] = 'r'; // 其他用户读权限
    if (mode & S_IWOTH) str[8] = 'w'; // 其他用户写权限
    if (mode & S_IXOTH) str[9] = 'x'; // 其他用户执行权限
}

int mysh_ls(char **args) {
    //显示详细信息标志
    int ls_option[100] ={0};
     int i;
    char *path =".";
     for ( i = 1; args[i] != NULL; i++) {
        // 如果参数不是以 "-" 开头，则它被认为是路径
        if (args[i][0] != '-') {
            path = args[i];
        }else{

            switch (args[i][1]) {
            case 'l':
                ls_option[ls_l] = 1;               
                break;
            case 'a':
                ls_option[ls_a] = 1;
                break;
            default:
                perror("Unrecognized option\n");
                return 1;
                break;

        }
        
    }
    }
    
    list_files(path, ls_option);
    return 1;
}

