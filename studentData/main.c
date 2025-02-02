#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 记录学生[]
struct Student 
{
	char name[50];	// 姓名
	int id;						// 学号
	int score;				// 成绩
};

#define MAX_STUDENTS 100 // 最大学生数量
#define FILENAME "students.txt" // 文件名

// 函数声明
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
		printf("空间已满，无法添加\n");
		return;
	}

	struct Student newStudent;
	printf("请输入学生姓名：");
	scanf("%s", newStudent.name);
	printf("请输入学生学号：");
	scanf("%d", &newStudent.id);
	printf("请输入学生成绩：");
	scanf("%d", &newStudent.score);

	students[*count] = newStudent;
	(*count)++;
	printf("添加成功\n");
}

void checkStudents(struct Student students[], int count)
{
	if (count == 0)
	{
		printf("无信息\n");
		return;
	}

	printf("学生列表：\n");
	printf("ID\t姓名\t\t成绩\n");
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
			printf("无信息\n");
			return;
		}

		int id;
			printf("请输入要修改的学生号：");
			scanf("%d", &id);

			for (int i = 0; i < count; i++)
			{
				if (students[i].id == id)
				{
					printf("找到学生：%s（学号：%d, 成绩：%d)\n", students[i].name, students[i].id, students[i].score);
					printf("新姓名：");
					scanf("%s", students[i].name);
					printf("新成绩：");
					scanf("%d", &students[i].score);
					printf("修改成功\n");
					return;
				}
			}
		printf("未找到学号为%d的学生\n", id);
}

	void deleteStudent(struct Student students[], int* count)
	{
		if (*count == 0)
		{
			printf("无信息\n");
			return;
		}

		int id;
		printf("请输入要删除的学生学号：");
		scanf("%d", &id);

		for (int i = 0; i < *count; i++)
		{
			if (students[i].id == id)
			{
				//将最后一个学生信息覆盖到当前位置
				students[i] = students[*count - 1];
				(*count)--;
				printf("删除成功\n");
				return;
			}
		}
		printf("未找到学号为%d的学生", id);
	}

	void saveToFile(struct Student students[], int count)
	{
		FILE* file = fopen(FILENAME, "w");
		if (file == NULL)
		{
			printf("文件打开失败，无法保存\n");
			return;
		}

		for (int i = 0; i < count; i++)
		{
			fprintf(file, "%s %d %d\n", students[i].name, students[i].id, students[i].score);
		}
		fclose(file);
		printf("已保存\n");
	}

	void loadFromFile(struct Student students[], int* count)
	{
		FILE* file = fopen(FILENAME, "r");
		if (file == NULL)
		{
			printf("文件打开失败，无法读取\n");
			return;
		}

		*count = 0;
		while (fscanf(file, "%s %d %d", students[*count].name, &students[*count].id, &students[*count].score) != EOF)
		{
			(*count)++;
		}
		fclose(file);
		printf("已读取\n");
	}

int main()
{
	struct Student students[MAX_STUDENTS]; // 学生数组
	int count = 0; // 当前学生数量

	int selection = 0; // 用户选择
	while (1)
	{
		// 显示菜单
		printf("\n欢迎使用学生管理系统：\n");
		printf("1、添加\n");
		printf("2、查看\n");
		printf("3、修改\n");
		printf("4、删除\n");
		printf("5、保存\n");
		printf("6、读取\n");
		printf("7、退出\n");
		printf("请选择操作：\n");
		scanf("%d", &selection);

		// 处理用户选择
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
			printf("已退出\n");
			return 0;
		default:
			printf("输入无效，请重新选择！\n");
		}
	}
	return 0;
}