#include "s_shell.h"

/**
 * _strchr - locates a character in a string,
 * @s: pointer to a string.
 * @c: character to be located
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}

/**
 * _strspn - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int i, j, state;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		state = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				state = 0;
				break;
			}
		}
		if (state == 1)
			break;
	}
	return (i);
}
/**
 * _isNumeric - checks if string passed is a numerical value
 *
 * @s: input string
 * Return: 1 if string is a number, else 0
 */
int _isNumeric(const char *s)
{
	unsigned int d;

	for (d = 0; s[d]; d++)
	{
		if (s[d] < 48 || s[d] > 57)
			return (0);
	}
	return (1);
}

/**
 * rev_string - Reverses a string
 * @s: string to be reversed
 * Return: void
 */
void rev_string(char *s)
{
	int count = 0, i, j;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}

