#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_file_info(struct dirent *entry, struct stat *info) {
    struct passwd *pw = getpwuid(info->st_uid);
    struct group *gr = getgrgid(info->st_gid);
    char date[20];
    strftime(date, sizeof(date), "%b %d %H:%M", localtime(&info->st_mtime));

    printf((S_ISDIR(info->st_mode)) ? "d" : "-");
    printf((info->st_mode & S_IRUSR) ? "r" : "-");
    printf((info->st_mode & S_IWUSR) ? "w" : "-");
    printf((info->st_mode & S_IXUSR) ? "x" : "-");
    printf((info->st_mode & S_IRGRP) ? "r" : "-");
    printf((info->st_mode & S_IWGRP) ? "w" : "-");
    printf((info->st_mode & S_IXGRP) ? "x" : "-");
    printf((info->st_mode & S_IROTH) ? "r" : "-");
    printf((info->st_mode & S_IWOTH) ? "w" : "-");
    printf((info->st_mode & S_IXOTH) ? "x" : "-");
    printf(" %2lu %s %s %5ld %s %s\n", info->st_nlink, pw->pw_name, gr->gr_name, info->st_size, date, entry->d_name);
}

int main() {
    struct dirent *entry;
    struct stat info;
    DIR *dp = opendir(".");
    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dp))) {
        if (stat(entry->d_name, &info) == -1) {
            perror("stat");
            return 1;
        }

        print_file_info(entry, &info);
    }

    closedir(dp);
    return 0;
}
