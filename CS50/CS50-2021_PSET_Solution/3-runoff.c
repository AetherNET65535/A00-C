#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RANK1_POINTS 100
#define RANK2_POINTS 50
#define RANK3_POINTS 30

// 结构体表示每个大人物的信息
typedef struct 
{
    char* name;
    int points;
}
noSmallAnymore;

// 函数声明
void getUserInput(noSmallAnymore* bigPeople, int user);
void printRankResult(noSmallAnymore* bigPeople);

int main() 
{
    // 初始化每个大人物的信息
    noSmallAnymore bigPeople[] = { {"kedo", 0}, {"egg", 0}, {"gan", 0} };

    int user = 3;

    for (int i = 0; i < user; i++) 
    {
        getUserInput(bigPeople, i);
    }

    printf("Result:\n");
    printRankResult(bigPeople);

    return 0;
}

void getUserInput(noSmallAnymore* bigPeople, int user) 
{
    char user_input[100];

    printf("User %d\n", user + 1);

    // 遍历每个排名
    for (int rank = 0; rank < 3; rank++) 
    {
        printf("Rank %d: ", rank + 1);
        scanf("%s", user_input);

        // 更新得分
        if (strcmp(user_input, bigPeople[0].name) == 0) 
        {
            bigPeople[0].points += (rank == 0) ? RANK1_POINTS : ((rank == 1) ? RANK2_POINTS : RANK3_POINTS);
        }
        else if (strcmp(user_input, bigPeople[1].name) == 0) 
        {
            bigPeople[1].points += (rank == 0) ? RANK1_POINTS : ((rank == 1) ? RANK2_POINTS : RANK3_POINTS);
        }
        else if (strcmp(user_input, bigPeople[2].name) == 0)
        {
            bigPeople[2].points += (rank == 0) ? RANK1_POINTS : ((rank == 1) ? RANK2_POINTS : RANK3_POINTS);
        }
    }
}

int cmp(const void* a, const void* b)
{
    const noSmallAnymore* left = (const noSmallAnymore*)a;
    const noSmallAnymore* right = (const noSmallAnymore*)b;

    return (right->points < left->points) - (left->points < right->points);
}

void printRankResult(noSmallAnymore* bigPeople) 
{
    
    // 打印结果
    qsort(bigPeople, 3, sizeof(noSmallAnymore), cmp);

    for (int i = 2; i >= 0; i--) {
        printf("Rank %d: %s - %dpt\n", 3-i, bigPeople[i].name, bigPeople[i].points);
    }
}
