#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 全局变量
char* input;

// 函数声明（优先级声明）
int parse_factor();     // 处理因子（高）
int parse_term();       // 处理乘除法（中）
int parse_expr();       // 处理加减法（低）

// 函数声明 （功能函数）
int ASCII_to_number();
void skip_space();

void skip_space()
{
    if (*input == ' ' || *input == '\t')
    {
        input++;
    }
}



int parse_factor();
{

}


int parse_term()
{
    int result = factor();
    skip_space();

    while(1)
    {
        if (*input == '*' || *input == '/')
        {
            char op = *input;
            input++;
            int num = parse_term();

            if (*input == '*')
            {
                result *= num;
            }
            else
            {
                result /= num;
            }
        }
        else
        {
            break;
        }
    }
    return result;
}

int parse_expr()
{
    int result = parse_term();
    skip_space();

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
    return result;
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