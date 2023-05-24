#include "s_shell.h"

/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}
/**
 * _strtok - splits a string using specified delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: splitted string
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /*Stores initial address*/
		i = _strlen(str);
		str_end = &str[i]; /*Stores final address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*end of string*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaks loop moves to next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replace delin with \0 */
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}


/**
 * split_line - tokenizes the input string
 *
 * @input: input string.
 * Return: tokenized string
 */
char **split_line(char *input)
{
	size_t byte_size;
	size_t i;
	char **tokens;
	char *token;

	byte_size = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (byte_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": Memory allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == byte_size)
		{
			byte_size += TOK_BUFSIZE;
			tokens = _reallocdptr(tokens, i, sizeof(char *) * byte_size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": Memory allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
