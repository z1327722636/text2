#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define wc_c 1
#define wc_l 2
#define wc_w 3

int mysh_wc(char **args)
{
    // 显示详细信息标志
    int wc_option[100] = {0};
    int i;

    for (i = 1; args[i] != NULL; i++) {
        // 如果参数不是以 "-" 开头，则它被认为是文件
        if (args[i][0] != '-') {
            // 打开文件进行统计操作
            FILE *file = fopen(args[i], "r");
            if (file == NULL) {
                perror("文件不存在,打开失败\n");
                return 1;
            }

            int lines = 0;
            int words = 0;
            int characters = 0;
            int in_word = 0;
            char ch;

            while ((ch = fgetc(file)) != EOF) {
                characters++;
                if (ch == '\n') {
                    lines++;
                }
                if (ch == ' ' || ch == '\t' || ch == '\n') {
                    if (in_word) {
                        words++;
                        in_word = 0;
                    }
                } else {
                    in_word = 1;
                }
            }

            fclose(file);

            // 根据选项打印统计结果
            if (wc_option[wc_c]) {
                printf("Characters: %d ", characters);
            }
            if (wc_option[wc_l]) {
                printf("Lines: %d ", lines);
            }
            if (wc_option[wc_w]) {
                printf("Words: %d ", words);
            }
            if(!wc_option[wc_c]&&!wc_option[wc_l]&&!wc_option[wc_w]){
               printf("Characters: %d ", characters); 
               printf("Lines: %d ", lines);
               printf("Words: %d ", words);
            }
            printf("%s\n", args[i]);
        }else{
        // 如果参数是选项，设置相应的标志
        switch (args[i][1]) {
            case 'c':
                wc_option[wc_c] = 1;
                break;
            case 'l':
                wc_option[wc_l] = 1;
                break;
            case 'w':
                wc_option[wc_w] = 1;
                break;
            default:
                perror("Unrecognized option\n");
                return 1;
                break;
        }
        }
        
    }
    
    return 1;
}
