#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));
	int randomNumber = rand();
	int userInput;
	
	printf ("Enter a Number: ");
	scanf ("%d", &userInput);

	printf ("Your Input: %d", userInput);

	while(1)
	{
		printf ("\n");

		if (userInput > randomNumber)
		{
			printf ("那么大怎么行呢？会受不了的\n");
		}
		else if (userInput < randomNumber)
		{
			printf ("不是吧？那么小吗......\n");
		}
		else
		{
			printf ("这大小很合适呢~\n");
			return 0;
		}
		
		printf ("再给你一次机会吧，杂鱼~\n在这输入: ");
		scanf ("%d", &userInput);
	}
}