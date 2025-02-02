#include <stdio.h>
#include <string.h>

#define BOT "小机器人"
#define USER "用户"

void wordDetect(char answer[])
{
	if (strstr(answer, "你好") != NULL)
	{
		printf("%s：你好呀！\n", BOT);
	}
	else if (strstr(answer, "天气") != NULL)
	{
		printf("%s：天气...我这里没天气呀！\n", BOT);
	}
	else if (strstr(answer, "AI") != NULL)
	{
		printf("%s：我不是AI，是%s！\n", BOT, BOT);
	}
	else if (strstr(answer, "可爱") != NULL)
	{
		printf("%s：%s也很可爱！\n", BOT, USER);
	}
	else
	{
		printf("%s：我是小孩，听不懂！\n", BOT);
	}
}

int main()
{
	char answer[50];

	printf("您好，欢迎使用chatBOT，请输入“退出”结束对话\n");
	printf("%s：您好，%s！\n", BOT, USER);

	while (1) 
	{
		printf("%s：", USER);
		scanf("%s", answer);

		if (strcmp(answer, "退出") == 0) 
		{
			printf("%s：再见！%s", BOT, USER);
			return 0;
		}
		else
		{
			wordDetect(answer);
		}
	}

	return 0;
}