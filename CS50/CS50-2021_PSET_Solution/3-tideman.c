#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RANK_POINTS 1

typedef struct
{
    char* name;
    int points;
} noSmallAnymore;

void getUserInput(noSmallAnymore* bigPeople, int user);
void printRankResult(noSmallAnymore* bigPeople);
int cmp(const void* a, const void* b);

int main()
{
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
    printf("Enter the big person's name: ");
    scanf("%s", user_input);

    for (int i = 0; i < 3; i++)
    {
        if (strcmp(user_input, bigPeople[i].name) == 0)
        {
            bigPeople[i].points += RANK_POINTS;
            break;
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
    qsort(bigPeople, 3, sizeof(noSmallAnymore), cmp);

    for (int i = 2; i >= 0; i--)
    {
        printf("Rank %d: %s - %dpt\n", 3 - i, bigPeople[i].name, bigPeople[i].points);
    }
}
