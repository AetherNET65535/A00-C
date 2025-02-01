#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>

int main()
{
    char plainText[100];
    
    // 请求用户输入想加密的文字
    printf("enterTheText: ");
    scanf("%s", plainText);

    // 打印用户输入的文字（对比用）
    printf("original_alpha: %s\n", plainText);

    // 加密字母
    for (int i = 0; i < strlen(plainText); i++)
    {
        if (plainText[i] >= 'A' && plainText[i] <= 'Z')
        {
            plainText[i] = (plainText[i] - 'A' + 1) % 26 + 'A';
        }
        else if (plainText[i] >= 'a' && plainText[i] <= 'z')
        {
            plainText[i] = (plainText[i] - 'a' + 1) % 26 + 'a';
        }
    }
    
    // 打印加密后的文字
    printf("after_alpha: %s\n", plainText);
    
    return 0;
}