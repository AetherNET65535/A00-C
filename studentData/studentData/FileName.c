#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��¼ѧ��[]
struct Student 
{
	char name[50];	// ����
	int id;						// ѧ��
	int score;				// �ɼ�
};

#define MAX_STUDENTS 100 // ���ѧ������
#define FILENAME "students.txt" // �ļ���

// ��������
void addStudent(struct Student students[], int *count);
void checkStudents(struct Student students[], int count);
void modifyStudent(struct Student students[], int count);
void deleteStudent(struct Student students[], int *count);
void saveToFile(struct Student students[], int count);
void loadFromFile(struct Student students[], int *count);

void addStudent(struct Student students[], int *count)
{
	if (*count >= MAX_STUDENTS)
	{
		printf("�ռ��������޷����\n");
		return;
	}

	struct Student newStudent;
	printf("������ѧ��������");
	scanf("%s", newStudent.name);
	printf("������ѧ��ѧ�ţ�");
	scanf("%d", &newStudent.id);
	printf("������ѧ���ɼ���");
	scanf("%d", &newStudent.score);

	students[*count] = newStudent;
	(*count)++;
	printf("��ӳɹ�\n");
}

void checkStudents(struct Student students[], int count)
{
	if (count == 0)
	{
		printf("����Ϣ\n");
		return;
	}

	printf("ѧ���б�\n");
	printf("ID\t����\t\t�ɼ�\n");
	printf("-----------------------------\n");

	for (int i = 0; i < count; i++)
	{
		printf("%d\t%-10s\t%d\n", students[i].id, students[i].name, students[i].score);
	}
}

void modifyStudent(struct Student students[], int count)
{
		if (count == 0)
		{
			printf("����Ϣ\n");
			return;
		}

		int id;
			printf("������Ҫ�޸ĵ�ѧ���ţ�");
			scanf("%d", &id);

			for (int i = 0; i < count; i++)
			{
				if (students[i].id == id)
				{
					printf("�ҵ�ѧ����%s��ѧ�ţ�%d, �ɼ���%d)\n", students[i].name, students[i].id, students[i].score);
					printf("��������");
					scanf("%s", students[i].name);
					printf("�³ɼ���");
					scanf("%d", &students[i].score);
					printf("�޸ĳɹ�\n");
					return;
				}
			}
		printf("δ�ҵ�ѧ��Ϊ%d��ѧ��\n", id);
}

	void deleteStudent(struct Student students[], int* count)
	{
		if (*count == 0)
		{
			printf("����Ϣ\n");
			return;
		}

		int id;
		printf("������Ҫɾ����ѧ��ѧ�ţ�");
		scanf("%d", &id);

		for (int i = 0; i < *count; i++)
		{
			if (students[i].id == id)
			{
				//�����һ��ѧ����Ϣ���ǵ���ǰλ��
				students[i] = students[*count - 1];
				(*count)--;
				printf("ɾ���ɹ�\n");
				return;
			}
		}
		printf("δ�ҵ�ѧ��Ϊ%d��ѧ��", id);
	}

	void saveToFile(struct Student students[], int count)
	{
		FILE* file = fopen(FILENAME, "w");
		if (file == NULL)
		{
			printf("�ļ���ʧ�ܣ��޷�����\n");
			return;
		}

		for (int i = 0; i < count; i++)
		{
			fprintf(file, "%s %d %d\n", students[i].name, students[i].id, students[i].score);
		}
		fclose(file);
		printf("�ѱ���\n");
	}

	void loadFromFile(struct Student students[], int* count)
	{
		FILE* file = fopen(FILENAME, "r");
		if (file == NULL)
		{
			printf("�ļ���ʧ�ܣ��޷���ȡ\n");
			return;
		}

		*count = 0;
		while (fscanf(file, "%s %d %d", students[*count].name, &students[*count].id, &students[*count].score) != EOF)
		{
			(*count)++;
		}
		fclose(file);
		printf("�Ѷ�ȡ\n");
	}

int main()
{
	struct Student students[MAX_STUDENTS]; // ѧ������
	int count = 0; // ��ǰѧ������

	int selection = 0; // �û�ѡ��
	while (1)
	{
		// ��ʾ�˵�
		printf("\n��ӭʹ��ѧ������ϵͳ��\n");
		printf("1�����\n");
		printf("2���鿴\n");
		printf("3���޸�\n");
		printf("4��ɾ��\n");
		printf("5������\n");
		printf("6����ȡ\n");
		printf("7���˳�\n");
		printf("��ѡ�������\n");
		scanf("%d", &selection);

		// �����û�ѡ��
		switch (selection)
		{
		case 1:
			addStudent(students, &count);
			break;
		case 2:
			checkStudents(students, count);
			break;
		case 3:
			modifyStudent(students, count);
			break;
		case 4:
			deleteStudent(students, &count);
			break;
		case 5:
			saveToFile(students, count);
			break;
		case 6:
			loadFromFile(students, &count);
			break;
		case 7:
			printf("���˳�\n");
			return 0;
		default:
			printf("������Ч��������ѡ��\n");
		}
	}
	return 0;
}