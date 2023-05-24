#include "s_shell.h"

/**
 * get_len - Get the length of number
 * @n: Number
 *
 * Return: Length
 */
int get_len(int n)
{
	unsigned int x;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		x = n * -1;
	}
	else
	{
		x = n;
	}
	while (x > 9)
	{
		lenght++;
		x = x / 10;
	}

	return (lenght);
}
/**
 * _itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *_itoa(int n)
{
	unsigned int x;
	int length = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0';

	if (n < 0)
	{
		x = n * -1;
		buffer[0] = '-';
	}
	else
	{
		x = n;
	}

	length--;
	do {
		*(buffer + length) = (x % 10) + '0';
		x = x / 10;
		length--;
	}
	while (x > 0)
		;
	return (buffer);
}

/**
 * my_atoi - converts a string to an integer
 * @str: input string
 *
 * Return: integer
 */
int my_atoi(char *str)
{
	unsigned int cIndex = 0, dCount = 0;
	unsigned int result = 0, sign = 1, multiplier = 1, i;

	while (*(str + cIndex) != '\0')
	{
		if (dCount > 0 && (*(str + cIndex) < '0' || *(str + cIndex) > '9'))
			break;
		if (*(str + cIndex) == '-')
			sign *= -1;
		if ((*(str + cIndex) >= '0') && (*(str + cIndex) <= '9'))
		{
			if (dCount > 0)
				multiplier *= 10;
			dCount++;
		}
		cIndex++;
	}
	for (i = cIndex - dCount; i < cIndex; i++)
	{
		result = result + ((*(str + i) - 48) * multiplier);
		multiplier /= 10;
	}
	return (result * sign);
}

