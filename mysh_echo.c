#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define echo_n 1
#define echo_e 2

// 解释转义字符并打印
void interpret_and_print(char *input) {
    char output[1000];
    int output_index = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '\\') {
            i++;
            if(input[i] == '\\'){
                i++;
            if (input[i] == 'a') {
                output[output_index++] = '\a';
            } else if (input[i] == 'b') {
                output[output_index++] = '\b';
            } else if (input[i] == 'c') {
                break; // 禁止尾随的换行符
            } else if (input[i] == 'f') {
                output[output_index++] = '\f';
            } else if (input[i] == 'n') {
                output[output_index++] = '\n';
            } else if (input[i] == 'r') {
                output[output_index++] = '\r';
            } else if (input[i] == 't') {
                output[output_index++] = '\t';
            } else if (input[i] == 'v') {
                output[output_index++] = '\v';
            } else if (input[i] == '\\') {
                output[output_index++] = '\\'; // 反斜线
            }else if (input[i] == 'x') {
                // 处理 \xNN 形式的16进制转义序列
                i++; // 跳过 'x'
                char hex[3] = {input[i], input[i + 1], '\0'};
                output[output_index++] = (char)strtol(hex, NULL, 16);
                i++;
            }else{
                i--;
                output[output_index++] = input[i];
            }
}else{
    output[output_index++] = input[i];
}
        } else {
            output[output_index++] = input[i];
        }
    }

    output[output_index] = '\0';
    printf("%s", output);
}


int mysh_echo(char **args) {
    // 显示详细信息标志
    int echo_option[100] = {0};
    char *non_option_args[100]; // 存储非选项参数的数组
    int non_option_count = 0;
    int i;

    for (i = 1; args[i] != NULL; i++) {
        // 如果参数不是以 "-" 开头，则它被认为是要打印的内容
        if (args[i][0] != '-') {
            non_option_args[non_option_count] = args[i];
            non_option_count++;
        }else{
            switch (args[i][1]) {
            case 'n':
                echo_option[echo_n] = 1;
                break;
            case 'e':
                echo_option[echo_e] = 1;
                break;
            default:
                perror("Unrecognized option\n");
                return 1;
                break;
        }
        }
    
    }

    for (i = 0; i < non_option_count; i++) {
        if (echo_option[echo_e]) {
            // 解释转义字符并打印
            interpret_and_print(non_option_args[i]);
        } else {
            printf("%s", non_option_args[i]);
        }

        if (i < non_option_count - 1) {
            printf(" "); // 添加空格
        }
    }

    if (!echo_option[echo_n]) {
        printf("\n"); // 如果没有 -n 参数，添加回车符
    }

    return 1;
}
