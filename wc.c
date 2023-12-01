#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("fopen");
        return 1;
    }

    // 定义一个变量line_count，用于记录行数
    int line_count = 0;
    int word_count = 0;
    int char_count = 0;

    char ch;
    int in_word = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        char_count++;
        if (ch == '\n')
        {
            line_count++;
        }
        if (ch == ' ' || ch == '\n' || ch == '\t')
        {
            in_word = 0;
        }
        else if (in_word == 0)
        {
            in_word = 1;
            word_count++;
        }
    }

    fclose(file);

    printf("Lines: %d\n", line_count);
    printf("Words: %d\n", word_count);
    printf("Characters: %d\n", char_count);
    return 0;
}
