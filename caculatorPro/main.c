#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* input;  // 全局指针，指向当前解析的字符位置

// 跳过空白字符
void skip_spaces() {
    while (*input == ' ' || *input == '\t') {
        input++;
    }
}

// 声明函数（用于相互调用）
int parse_expr();

// 解析多位数（含负数）
int parse_number() {
    int sign = 1;
    int num = 0;
    
    skip_spaces();
    if (*input == '-') {  // 处理负数符号
        sign = -1;
        input++;
        skip_spaces();
    }
    
    while (isdigit(*input)) {
        num = num * 10 + (*input - '0');
        input++;
    }
    return sign * num;
}

// 解析因子（数字或括号表达式）
int parse_factor() {
    skip_spaces();
    int result;
    
    if (*input == '(') {  // 处理括号
        input++;
        result = parse_expr();
        skip_spaces();
        if (*input != ')') {
            fprintf(stderr, "错误：缺少右括号\n");
            exit(EXIT_FAILURE);
        }
        input++;
    } else if (isdigit(*input) || *input == '-') {  // 处理数字和显式负数
        result = parse_number();
    } else {
        fprintf(stderr, "错误：期待数字或括号，找到 '%c'\n", *input);
        exit(EXIT_FAILURE);
    }
    return result;
}

// 解析项（显式乘除运算）
int parse_term() {
    int result = parse_factor();  // 获取第一个因子
    
    while (1) {
        skip_spaces();
        if (*input == '*' || *input == '/') {
            char op = *input;
            input++;
            int num = parse_factor();
            if (op == '*') {
                result *= num;
            } else {
                if (num == 0) {
                    fprintf(stderr, "错误：除以零\n");
                    exit(EXIT_FAILURE);
                }
                result /= num;
            }
        } else {
            break;  // 结束当前项解析
        }
    }
    return result;
}

// 解析表达式（加减运算）
int parse_expr() {
    int result = parse_term();  // 获取第一个项
    
    while (1) {
        skip_spaces();
        if (*input == '+' || *input == '-') {
            char op = *input;
            input++;
            int num = parse_term();
            if (op == '+') {
                result += num;
            } else {
                result -= num;
            }
        } else {
            break;  // 结束表达式解析
        }
    }
    return result;
}

int main() {
    char buffer[1024];
    printf("请输入表达式（必须使用显式乘号）：\n");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "读取输入失败\n");
        return EXIT_FAILURE;
    }
    
    input = buffer;
    int result = parse_expr();
    
    // 验证是否解析完整个输入
    skip_spaces();
    if (*input != '\0' && *input != '\n') {
        fprintf(stderr, "错误：无效字符 '%c'（是否忘记乘号？）\n", *input);
        return EXIT_FAILURE;
    }
    
    printf("计算结果：%d\n", result);
    return 0;
}
