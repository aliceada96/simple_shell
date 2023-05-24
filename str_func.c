#include "s_shell.h"

/**
 * _strlen - Returns the length of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	;
	return (len);
}
/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}

/**
 * _strdup - duplicates a string in the heap memory.
 * @s: Char pointer string
 * Return: duplicated string
 */
char *_strdup(const char *s)
{
	char *new;
	size_t length;

	length = _strlen(s);
	new = malloc(sizeof(char) * (length + 1));
	if (new == NULL)
		return (NULL);
	mem_copy(new, s, length + 1);
	return (new);
}
/**
 * _strcat - concatenates two strings
 * @dest: Pinter the dest of the copied string,char
 * @src: const character pointer the source of string
 * Return: dest
 */
char *_strcat(char *dest, const char *src)
{
	int a;
	int b;

	for (a = 0; dest[a] != '\0'; a++)
		;

	for (b = 0; src[b] != '\0'; b++)
	{
		dest[a] = src[b];
		a++;
	}

	dest[a] = '\0';
	return (dest);
}
/**
 * _strcmp - Function that compares two strings.
 * @str1: 1st string
 * @str2: 2nd string
 * Return: Always 0.
 */
int _strcmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] == str2[i] && str1[i]; i++)
		;

	if (str1[i] > str2[i])
		return (1);
	if (str1[i] < str2[i])
		return (-1);
	return (0);
}
