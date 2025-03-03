#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *src;  // 全局指针，用于遍历输入字符串

// 跳过空格
void skip_spaces() {
    while (*src == ' ') src++;
}

// 新增：处理一元负号的核心逻辑
int parse_factor() {
    skip_spaces();
    int sign = 1;  // 默认符号为正
    
    // 检查是否有一元负号
    if (*src == '-') {
        sign = -1;
        src++;  // 跳过负号
        skip_spaces();
        
        // 检查负号后是否是合法内容（数字或括号）
        if (!isdigit(*src) && *src != '(') {
            printf("错误：负号后缺少数字或括号\n");
            exit(1);
        }
    }
    
    int result = 0;
    if (*src == '(') {
        src++;  // 跳过'('
        result = parse_factor();  // 递归解析括号内的表达式
        skip_spaces();
        if (*src != ')') {
            printf("错误：缺少右括号\n");
            exit(1);
        }
        src++;  // 跳过')'
    } else if (isdigit(*src)) {
        while (isdigit(*src)) {
            result = result * 10 + (*src - '0');
            src++;
        }
    } else {
        printf("错误：非法字符 '%c'\n", *src);
        exit(1);
    }
    
    return sign * result;  // 应用符号
}

// 解析乘除法
int parse_term() {
    int result = parse_factor();
    skip_spaces();
    
    while (*src == '*' || *src == '/') {
        char op = *src;
        src++;
        int factor = parse_factor();
        
        if (op == '*') {
            result *= factor;
        } else {
            if (factor == 0) {
                printf("错误：除数为零\n");
                exit(1);
            }
            result /= factor;
        }
        skip_spaces();
    }
    return result;
}

// 解析加减法
int parse_expression() {
    int result = parse_term();
    skip_spaces();
    
    while (*src == '+' || *src == '-') {
        char op = *src;
        src++;
        int term = parse_term();
        
        if (op == '+') {
            result += term;
        } else {
            result -= term;
        }
        skip_spaces();
    }
    return result;
}

int main() {
    char input[1024];
    printf("请输入表达式（支持+-*/和括号）：\n");
    fgets(input, sizeof(input), stdin);
    
    src = input;
    int result = parse_expression();
    
    printf("计算结果：%d\n", result);
    return 0;
}
 