#include <stdio.h>
#include <string.h>

int main()
{
    // 需要替换的字母
    char ori[] = "RSTUVWXYZLC";
    char oris[] = "rstuvwxyzlc";

    // 对应密钥
    char key[] = "1234567890.";
    char keys[] = "1234567890.";

    // 明文
    char plainText[100];

    // 请求用户输入明文
    printf("enterTheText: ");
    fgets(plainText, sizeof(plainText), stdin);

    // 遍历输入的字符
    for (int i = 0; i < strlen(plainText); i++)
    {
        // 处理大写字母
        for (int j = 0; j < strlen(ori); j++)
        {
            if (plainText[i] == ori[j])
            {
                plainText[i] = key[j];
                break;
            }
        }

        // 处理小写字母
        for (int j = 0; j < strlen(oris); j++)
        {
            if (plainText[i] == oris[j])
            {
                plainText[i] = keys[j];
                break;
            }
        }
    }

    // 打印加密后的密文
    printf("after_alpha: %s\n", plainText);

    return 0;
}
