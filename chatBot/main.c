#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)

#include <stdio.h>
#include <string.h>

#define BOT "С������"
#define USER "�û�"

void wordDetect(char answer[])
{
	if (strstr(answer, "���") != NULL)
	{
		printf("%s�����ѽ��\n", BOT);
	}
	else if (strstr(answer, "����") != NULL)
	{
		printf("%s������...������û����ѽ��\n", BOT);
	}
	else if (strstr(answer, "AI") != NULL)
	{
		printf("%s���Ҳ���AI����%s��\n", BOT, BOT);
	}
	else if (strstr(answer, "�ɰ�") != NULL)
	{
		printf("%s��%sҲ�ܿɰ���\n", BOT, USER);
	}
	else
	{
		printf("%s������С������������\n", BOT);
	}
}

int main()
{
	char answer[50];

	printf("���ã���ӭʹ��chatBOT�������롰�˳��������Ի�\n");
	printf("%s�����ã�%s��\n", BOT, USER);

	while (1) 
	{
		printf("%s��", USER);
		scanf("%s", answer);

		if (strcmp(answer, "�˳�") == 0) 
		{
			printf("%s���ټ���%s", BOT, USER);
			return 0;
		}
		else
		{
			wordDetect(answer);
		}
	}

	return 0;
}