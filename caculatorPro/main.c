#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 全局变量
char* input;

// 函数声明（优先级声明）
int parse_factor();     // 处理因子（高）
int parse_term();       // 处理乘除法（中）
int parse_expr();       // 处理加减法（低）

// 函数声明（功能函数）
int ASCII_to_number();
void skip_space();

int ASCII_to_number()
{
    int sign = 1; // 正数与负数的标识符，默认正数
    int num = 0; // 用于计算多位数，和之前写的汇编整数计算器差不多

    if (*input == '-')
    {
        sign = -1;
        input++;
        skip_space();
    }

    while (isdigit(*input))
    {
        num = num * 10 + (*input - '0');
        input++;
    }
    return num * sign;
}

void skip_space()
{
    if (*input == ' ' || *input == '\t')
    {
        input++;
    } 
}

int parse_factor()
{
    skip_space();

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