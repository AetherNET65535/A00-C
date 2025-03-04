#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 全局变量
char* input;

// 函数声明
int parse_expr();
int parse_term();
int parse_factor();

int parse_expr()
{
    int result = parse_term();

    while(1)
    {
        if (*input == '+' || *input == '-')
        {
            char op = *input;
            input++;
            int num = parse_term();

            if (*input == '+')
            {
                result += num;
            }
            else
            {
                result -= num;
            }
        }
        else
        {
            break;
        }
    }
}

void skip_space()
{
    if (*input == ' ' || *input == '\t')
    {
        input++;
    }
}

int main ()
{
    char box [1024];
    printf ("请输入表达式（必须使用显式乘法）：\n");
    if (fgets(box, sizeof(box), stdin) == NULL)
    {
        printf ("看到这条表示出BUG了！！ [获取用户输入字符串]\n");
        return 0;
    }

    input = box;
    int result = parse_expr(); 
}