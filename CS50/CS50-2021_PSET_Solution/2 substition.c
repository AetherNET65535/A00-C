#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>

int main()
{
    // ABC
    char ori[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char oris[100] = "abcdefghijklmnopqrstuvwxyz";

    // 密钥
    char key[100] = "LSPHENTAIZXBODWGQCFRJVUKYM";
    char keys[100] = "lsphentaizxbodwgqcfrjvukym";

    //明文
    char plainText[100];

    // 请求用户输入明文
    printf("enterTheText: ");
    fgets(plainText, sizeof(plainText), stdin);

    int n = 0;

    for (int i = 0; i < strlen(plainText); i++)
    {
        if (plainText[i] >= 'A' && plainText[i] <= 'Z')
        {
            int index = plainText[i] - 'A';
            plainText[i] = key[index];
        }
        else if (plainText[i] >= 'a' && plainText[i] <= 'z')
        {
            int indexs = plainText[i] - 'a';
            plainText[i] = keys[indexs];
        }
    }

    // 打印加密后的密文
    printf("after_alpha:%s\n", plainText);

    return 0;

}