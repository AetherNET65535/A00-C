#include <stdio.h>
#include <string.h>

// 书本信息结构体
struct book 
{
	char title [50];
	char author [50];
	char releaseCom [50];
	char releaseDate[25];
};

// define分区
#define MAX_BOOKS 10
#define FILENAME "book.txt"

// 函数声明
void addBook(struct book nowBook[], int *count);
void checkBook(struct book nowBook[], int count);
void editBook(struct book nowBook[], int count);
void deleteBook(struct book nowBook[], int* count);
void saveBookFile(struct book nowBook[], int count);
void loadBookFile(struct book nowBook[], int* count);
void sortBook(struct book nowBook[], int count, int byTitle);

void addBook(struct book nowBook[], int *count)
{
	if (*count >= MAX_BOOKS)
	{
		printf("空间自满，无法添加\n");
		return;
	}

	struct book newBook;
	printf("请输入标题：");
	scanf("%s", newBook.title);
	printf("请输入作者名：");
	scanf("%s", newBook.author);
	printf("请输入发行商：");
	scanf("%s", newBook.releaseCom);
	printf("请输入发行日期：");
	scanf("%s", newBook.releaseDate);


	nowBook[*count] = newBook;
	(*count)++;
	printf("添加成功\n");
}

void checkBook(struct book nowBook[], int count)
{
	if (count == 0)
	{
		printf("无信息\n");
		return;
	}

	printf("书本列表：\n");
	printf("标题\t\t作者\t发行商\t发行日期\n");
	printf("----------------------------------------------------------\n");

	for (int i = 0; i < count; i++)
	{
		printf("%s\t\t%s\t%s\t%s\n", nowBook[i].title, nowBook[i].author, nowBook[i].releaseCom, nowBook[i].releaseDate);
	}
}

void editBook(struct book nowBook[], int count)
{
	if (count == 0)
	{
		printf("无信息\n");
		return;
	}

	char title[50];
	printf("请输入要编辑的书的标题：");
	scanf("%s", title);

	for (int i = 0; i < count; i++)
	{
		if (strcmp(nowBook[i].title, title)==0)
		{
			printf("已找到：%s\t\t%s\t%s\t%s\n", nowBook[i].title, nowBook[i].author, nowBook[i].releaseCom, nowBook[i].releaseDate);
			printf("新标题：");
			scanf("%s", nowBook[i].title);
			printf("新作者：");
			scanf("%s", nowBook[i].author);
			printf("新发行商：");
			scanf("%s", nowBook[i].releaseCom);
			printf("新发行日期：");
			scanf("%s", nowBook[i].releaseDate);
		}
	}
	printf("未找到标题为%s的书本", title);
	return;
}

void deleteBook(struct book nowBook[], int* count)
{
	if (count == 0)
	{
		printf("无信息\n");
		return;
	}

	char title[50];
	printf("请输入要删除的书的标题：");
	scanf("%s", title);

	char yn;

	for (int i = 0; i < count; i++)
	{
		if (strcmp(nowBook[i].title, title)==0)
		{
			printf("已找到：%s\t\t%s\t%s\t%s\n", nowBook[i].title, nowBook[i].author, nowBook[i].releaseCom, nowBook[i].releaseDate);
			printf("确认删除？(y/n)\n");
			scanf(" %c", &yn);
			switch (yn)
			{
			case 'y':
				nowBook[i] = nowBook[*count - 1];
				(*count)--;
				printf("删除成功\n");
				return;
			case 'n':
				return;
			}
		}
	}
	printf("未找到标题为%s的书本", title);
	return;
}

void saveBookFile(struct book nowBook[], int count)
{
	FILE* file = fopen(FILENAME, "wb");
	if (file == NULL)
	{
		printf("文件打开失败，无法保存\n");
		return;
	}

	if (fwrite(&count, sizeof(int), 1, file) != 1) 
	{
		printf("保存书本数量失败\n");
		fclose(file);
		return;
	}

	if (fwrite(nowBook, sizeof(struct book), count, file) != (size_t)count)
	{
		printf("保存书本数据失败\n");
		fclose(file);
		return;
	}
	fclose(file);
	printf("已保存\n");
}

void loadBookFile(struct book nowBook[], int *count)
{
	FILE* file = fopen(FILENAME, "r");
	if (file == NULL)
	{
		printf("文件打开失败，无法保存\n");
		return;
	}

	if (fread(count, sizeof(int), 1, file) != 1) 
	{
		printf("读取书本数量失败\n");
		fclose(file);
		return;
	}

	
	if (*count > MAX_BOOKS)
	{
		printf("文件内容超出最大存储限制\n");
		fclose(file);
		*count = 0; 
		return;
	}

	if (fread(nowBook, sizeof(struct book), *count, file) != (size_t)(*count))
	{
		printf("读取书本数据失败\n");
		fclose(file);
		*count = 0; 
		return;
	}

	fclose(file);
	printf("已读取\n");
}

void sortBook(struct book nowBook[], int count, int byTitle)
{
	if (count <= 1)
	{
		printf("无需排序\n");
		return;
	}

	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			int compare;
			if (byTitle)
			{
				compare = strcmp(nowBook[j].title, nowBook[j + 1].title);
			}
			else
			{
				compare = strcmp(nowBook[j].releaseDate, nowBook[j + 1].releaseDate);
			}

			if (compare > 0)
			{
				struct book temp = nowBook[j];
				nowBook[j] = nowBook[j + 1];
				nowBook[j + 1] = temp;
			}
		}
	}

	if (byTitle)
	{
		printf("已按书名排序\n");
	}
	else
	{
		printf("已按出版日期排序\n");
	}
}

int main()
{
	struct book nowBook[MAX_BOOKS];
	int count = 0;

	int selection = 0;
	while (1)
	{
		printf("\n欢迎使用图书管理系统：\n");
		printf("1、添加\n");
		printf("2、查看\n");
		printf("3、编辑\n");
		printf("4、删除\n");
		printf("5、保存\n");
		printf("6、读取\n");
		printf("7、退出\n");
		printf("请选择操作：\n");
		scanf("%d", &selection);

		switch (selection)
		{
		case 1:
			addBook(nowBook, &count);
			break;
		case 2:
			checkBook(nowBook, count);
			break;
		case 3:
			editBook(nowBook, count);
			break;
		case 4:
			deleteBook(nowBook, &count);
			break;
		case 5:
			saveBookFile(nowBook, count);
			break;
		case 6:
			loadBookFile(nowBook, &count);
			break;
		case 7:
			printf("已退出\n");
			return 0;
		case 8:
			printf("选择排序方法：\n1、按书名\n2、按出版日期\n");
			int sortOption;
			scanf("%d", &sortOption);
			if (sortOption == 1)
			{
				sortBook(nowBook, count, 1);
			}
			else if (sortOption == 2)
			{
				sortBook(nowBook, count, 0);
			}
			else
			{
				printf("无效的选择\n");
			}
		default:
			printf("输入无效，请重新输入\n");
		}
	}
	return 0;
}