#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main()
{
    char p = '#';
    int x, y, z, n;

    do
    {
        //ask user how many heights want make
        printf("type a num 1-8: ");
        scanf("%d", &n);

        //check check bro is stupid asshole or not
        if (n < 1 || n > 8)
        {
            while (getchar() != '\n');
        }
    } while (n < 1 || n > 8);
        
    //make left piramid
    for (x = 1; x <= n; x++)
    {
        for (y = n - x; y > 0; y--)
            printf(" ");

        for (z = 1; z <= x; z++)
        {
            printf("%c", p);
        }
     
        //make a space and right piramid
        printf(" ");

        for (z = 1; z <= x; z++)
        {
            printf("%c", p);
        }
        printf("\n");
    }

	return 0;
}