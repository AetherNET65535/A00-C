#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

// 验证信用卡号是否有效 -Luhn 算法-
int isValidCreditCard(long long int creditCardNumber)
{
	int sum = 0;
	int digitCount = 0;

	while (creditCardNumber > 0)
	{
		int digit = creditCardNumber % 10;
		creditCardNumber /= 10;
		digitCount++;

		// 每隔两个数字及之后的数字应用 -Luhn 算法-
		if (digitCount % 2 == 0)
		{
			digit *= 2;

			// 将乘积的数字相加
			sum += (digit % 10) + (digit / 10);
		}
		else
		{
			sum += digit;
		}
	}

	// 总数最后一位数（如果是0就对）
	return (sum % 10 == 0);
}

// 信用卡品牌判断
void checkCreditCardBrand(long long int creditCardNumber)
{
	int digitCount = 0;
	int firstTwoDigits = 0;

	// 获取前两位数
	while (creditCardNumber > 0)
	{
		int digit = creditCardNumber % 10;
		creditCardNumber /= 10;
		digitCount++;

		if (digitCount == 15 || digitCount == 16)
		{
			firstTwoDigits = digit * 10 + creditCardNumber % 10;
		}
	}

	// 根据条件检查信用卡品牌
	if ((digitCount == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37)) ||
		(digitCount == 16 && (firstTwoDigits >= 51 && firstTwoDigits <= 55)))
	{
		printf("MASTERCARD\n");
	}
	else if ((digitCount == 13 || digitCount == 16) && (firstTwoDigits / 10 == 4))
	{
		printf("VISA\n");
	}
	else if (digitCount == 16 && firstTwoDigits / 10 == 4)
	{
		printf("VISA\n");
	}
	else {
		printf("INVALID\n");
	}
}

int main()
{
	// 请求用户输入信用卡号码
	printf("Number: ");
	long long int creditCardNumber;
	scanf("%lld", &creditCardNumber);

	// 验证信用卡号码
	if (isValidCreditCard(creditCardNumber))
	{
		// 检查信用卡品牌
		checkCreditCardBrand(creditCardNumber);
	}
	else
	{
		printf("INVALID\n");
	}

	return 0;
}
