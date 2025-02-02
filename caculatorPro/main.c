#include <stdio.h>
#include <string.h>

void caculate();
void historySearch();

char history[10][50];
int historyTime = 0;

int main()
{
    int selection;

    while (1)
    {
        printf("1、计算器\n2、历史记录\n3、退出\n请输入您想使用的功能：");
        scanf("%d", &selection);

        if (selection == 1)
        {
            caculate();
        }
        else if (selection == 2)
        {
            historySearch();
        }
        else if (selection == 3)
        {
            return 0;
        }
        else
        {
            printf("睡糊涂啦？再打一次吧：");
        }
    }
}

void caculate()
{
    int numberOne, numberTwo, answer;
    char  operator;

    while (1)
    {
        printf("请输入第一个数字：\n");
        scanf("%d", &numberOne);

        printf("请输入运算符：\n");
        scanf(" %c", &operator);

        printf("请输入第二个数字：\n");
        scanf("%d", &numberTwo);

        if (operator == '*')
        {
            answer = (numberOne * numberTwo);
            printf("%d * %d = %d", numberOne, numberTwo, answer);
            sprintf(history[historyTime++], "%d * %d = %d", numberOne, numberTwo, answer);
        }
        else if (operator == '+')
        {
            answer = (numberOne + numberTwo);
            printf("%d + %d = %d", numberOne, numberTwo, answer);
            sprintf(history[historyTime++], "%d + %d = %d", numberOne, numberTwo, answer);
        }
        else if (operator == '-')
        {
            answer = (numberOne - numberTwo);
            printf("%d - %d = %d", numberOne, numberTwo, answer);
            sprintf(history[historyTime++], "%d - %d = %d", numberOne, numberTwo, answer);
        }
        else if (operator == '/')
        {
            if (numberTwo != 0)
            {
                answer = (numberOne / numberTwo);
                printf("%d / %d = %d", numberOne, numberTwo, answer);
                sprintf(history[historyTime++], "%d / %d = %d", numberOne, numberTwo, answer);
            }
            else
            {
                printf("不能除以零，请重新输入\n");
                continue;
            }
        }
        else
        {
            printf("无效的运算符，请重新输入\n");
            continue;
        }

        char yn;
        printf("是否继续？\nY/N：");
        scanf(" %c", &yn);

        if (yn == 'n' || yn == 'N')
        {
            break;
        }
        else if (yn != 'y' || yn != 'Y')
        {
            printf("无效输入，请重新输入\n");
        }
        else
        {
            printf("睡糊涂啦？再打一次吧：");
        }
    }
}

void historySearch()
{
    printf("历史记录：\n");
    for (int i = 0; i < historyTime; i++)
    {
        printf("\n%d: %s\n", i + 1, history[i]);
    }
}