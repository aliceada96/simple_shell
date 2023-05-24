#include "s_shell.h"

/**
 * index_char1 - finds first characters index
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error else 0
 */
int index_char1(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * dup_char - counts a duplicated char
 *
 * @input: input string
 * @i: index
 * Return: 1
 */
int dup_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (dup_char(input - 1, i + 1));

	return (i);
}

/**
 * error_finder - find syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last character
 * Return: index of error else 0
 */
int error_finder(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_finder(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = dup_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = dup_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_finder(input + 1, i + 1, *input));
}

/**
 * p_error - prints when there is syntax error
 *
 * @arg: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: void
 */
void p_error(our_shell *arg, char *input, int i, int bool)
{
	char *txt, *txt2, *txt3, *err, *counter;
	int len;

	if (input[i] == ';')
	{
		if (bool == 0)
			txt = (input[i + 1] == ';' ? ";;" : ";");
		else
			txt = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		txt = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		txt = (input[i + 1] == '&' ? "&&" : "&");

	txt2 = " Syntax errror \"";
	txt3 = "\" unexpected input\n";
	counter = _itoa(arg->counter);
	len = _strlen(arg->av[0]) + _strlen(counter);
	len += _strlen(txt) + _strlen(txt2) + _strlen(txt3) + 2;

	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(counter);
		return;
	}
	_strcpy(err, arg->av[0]);
	_strcat(err, ": ");
	_strcat(err, counter);
	_strcat(err, txt2);
	_strcat(err, txt);
	_strcat(err, txt3);
	_strcat(err, "\0");

	write(STDERR_FILENO, err, len);
	free(err);
	free(counter);
}

/**
 * syntax_error - finds and prints syntax errors
 *
 * @arg: data struct
 * @input: input string
 * Return: 1 if there is an error else 0
 */
int syntax_error(our_shell *arg, char *input)
{
	int start = 0;
	int char1 = 0;
	int i = 0;

	char1 = index_char1(input, &start);
	if (char1 == -1)
	{
		p_error(arg, input, start, 0);
		return (1);
	}

	i = error_finder(input + start, 0, *(input + start));
	if (i != 0)
	{
		p_error(arg, input, start + i, 1);
		return (1);
	}

	return (0);
}
