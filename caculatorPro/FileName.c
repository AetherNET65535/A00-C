#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
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
        printf("1��������\n2����ʷ��¼\n3���˳�\n����������ʹ�õĹ��ܣ�");
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
            printf("˯��Ϳ�����ٴ�һ�ΰɣ�");
        }
    }
}

void caculate()
{
    int numberOne, numberTwo, answer;
    char  operator;

    while (1)
    {
        printf("�������һ�����֣�\n");
        scanf("%d", &numberOne);

        printf("�������������\n");
        scanf(" %c", &operator);

        printf("������ڶ������֣�\n");
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
                printf("���ܳ����㣬����������\n");
                continue;
            }
        }
        else
        {
            printf("��Ч�������������������\n");
            continue;
        }

        char yn;
        printf("�Ƿ������\nY/N��");
        scanf(" %c", &yn);

        if (yn == 'n' || yn == 'N')
        {
            break;
        }
        else if (yn != 'y' || yn != 'Y')
        {
            printf("��Ч���룬����������\n");
        }
        else
        {
            printf("˯��Ϳ�����ٴ�һ�ΰɣ�");
        }
    }
}

void historySearch()
{
    printf("��ʷ��¼��\n");
    for (int i = 0; i < historyTime; i++)
    {
        printf("\n%d: %s\n", i + 1, history[i]);
    }
}
