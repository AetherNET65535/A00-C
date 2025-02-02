#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
#include <stdio.h>
#include <string.h>

// �鱾��Ϣ�ṹ��
struct book 
{
	char title [50];
	char author [50];
	char releaseCom [50];
	char releaseDate[25];
};

// define����
#define MAX_BOOKS 10
#define FILENAME "book.txt"

// ��������
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
		printf("�ռ��������޷����\n");
		return;
	}

	struct book newBook;
	printf("��������⣺");
	scanf("%s", newBook.title);
	printf("��������������");
	scanf("%s", newBook.author);
	printf("�����뷢���̣�");
	scanf("%s", newBook.releaseCom);
	printf("�����뷢�����ڣ�");
	scanf("%s", newBook.releaseDate);


	nowBook[*count] = newBook;
	(*count)++;
	printf("��ӳɹ�\n");
}

void checkBook(struct book nowBook[], int count)
{
	if (count == 0)
	{
		printf("����Ϣ\n");
		return;
	}

	printf("�鱾�б�\n");
	printf("����\t\t����\t������\t��������\n");
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
		printf("����Ϣ\n");
		return;
	}

	char title[50];
	printf("������Ҫ�༭����ı��⣺");
	scanf("%s", title);

	for (int i = 0; i < count; i++)
	{
		if (strcmp(nowBook[i].title, title)==0)
		{
			printf("���ҵ���%s\t\t%s\t%s\t%s\n", nowBook[i].title, nowBook[i].author, nowBook[i].releaseCom, nowBook[i].releaseDate);
			printf("�±��⣺");
			scanf("%s", nowBook[i].title);
			printf("�����ߣ�");
			scanf("%s", nowBook[i].author);
			printf("�·����̣�");
			scanf("%s", nowBook[i].releaseCom);
			printf("�·������ڣ�");
			scanf("%s", nowBook[i].releaseDate);
		}
	}
	printf("δ�ҵ�����Ϊ%s���鱾", title);
	return;
}

void deleteBook(struct book nowBook[], int* count)
{
	if (count == 0)
	{
		printf("����Ϣ\n");
		return;
	}

	char title[50];
	printf("������Ҫɾ������ı��⣺");
	scanf("%s", title);

	char yn;

	for (int i = 0; i < count; i++)
	{
		if (strcmp(nowBook[i].title, title)==0)
		{
			printf("���ҵ���%s\t\t%s\t%s\t%s\n", nowBook[i].title, nowBook[i].author, nowBook[i].releaseCom, nowBook[i].releaseDate);
			printf("ȷ��ɾ����(y/n)\n");
			scanf(" %c", &yn);
			switch (yn)
			{
			case 'y':
				nowBook[i] = nowBook[*count - 1];
				(*count)--;
				printf("ɾ���ɹ�\n");
				return;
			case 'n':
				return;
			}
		}
	}
	printf("δ�ҵ�����Ϊ%s���鱾", title);
	return;
}

void saveBookFile(struct book nowBook[], int count)
{
	FILE* file = fopen(FILENAME, "wb");
	if (file == NULL)
	{
		printf("�ļ���ʧ�ܣ��޷�����\n");
		return;
	}

	if (fwrite(&count, sizeof(int), 1, file) != 1) 
	{
		printf("�����鱾����ʧ��\n");
		fclose(file);
		return;
	}

	if (fwrite(nowBook, sizeof(struct book), count, file) != (size_t)count)
	{
		printf("�����鱾����ʧ��\n");
		fclose(file);
		return;
	}
	fclose(file);
	printf("�ѱ���\n");
}

void loadBookFile(struct book nowBook[], int *count)
{
	FILE* file = fopen(FILENAME, "r");
	if (file == NULL)
	{
		printf("�ļ���ʧ�ܣ��޷�����\n");
		return;
	}

	if (fread(count, sizeof(int), 1, file) != 1) 
	{
		printf("��ȡ�鱾����ʧ��\n");
		fclose(file);
		return;
	}

	
	if (*count > MAX_BOOKS)
	{
		printf("�ļ����ݳ������洢����\n");
		fclose(file);
		*count = 0; 
		return;
	}

	if (fread(nowBook, sizeof(struct book), *count, file) != (size_t)(*count))
	{
		printf("��ȡ�鱾����ʧ��\n");
		fclose(file);
		*count = 0; 
		return;
	}

	fclose(file);
	printf("�Ѷ�ȡ\n");
}

void sortBook(struct book nowBook[], int count, int byTitle)
{
	if (count <= 1)
	{
		printf("��������\n");
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
		printf("�Ѱ���������\n");
	}
	else
	{
		printf("�Ѱ�������������\n");
	}
}

int main()
{
	struct book nowBook[MAX_BOOKS];
	int count = 0;

	int selection = 0;
	while (1)
	{
		printf("\n��ӭʹ��ͼ�����ϵͳ��\n");
		printf("1�����\n");
		printf("2���鿴\n");
		printf("3���༭\n");
		printf("4��ɾ��\n");
		printf("5������\n");
		printf("6����ȡ\n");
		printf("7���˳�\n");
		printf("��ѡ�������\n");
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
			printf("���˳�\n");
			return 0;
		case 8:
			printf("ѡ�����򷽷���\n1��������\n2������������\n");
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
				printf("��Ч��ѡ��\n");
			}
		default:
			printf("������Ч������������\n");
		}
	}
	return 0;
}