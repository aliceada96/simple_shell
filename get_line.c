#include "s_shell.h"

/**
 * check_line - checks user input
 *
 * @lineptr: User input
 * @n: size of line
 * @buff: string to call
 * @i: size of buffer
 *
 * Return: void
 */

void check_line(char **lineptr, size_t *n, char *buff, size_t i)
{
	if (*lineptr == NULL)
	{
		if  (i > BUFSIZE)
			*n = i;

		else
			*n = BUFSIZE;
		*lineptr = buff;
	}
	else if (*n < i)
	{
		if (i > BUFSIZE)
			*n = i;
		else
			*n = BUFSIZE;
		*lineptr = buff;
	}
	else
	{
		_strcpy(*lineptr, buff);
		free(buff);
	}
}

/**
 * get_line - accepts input from user
 * Description: Accepts user input
 *
 * @lineptr: user input
 * @stream: file to stream
 * @n: size of line
 *
 * Return: readchars
 */

ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t input = 0;
	ssize_t readchars = 0;
	char *buffer = NULL;
	char x = 'b';
	int j;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);

	while (x != '\n')
	{
		j = read(STDIN_FILENO, &x, 1);
		if (j == -1 || (j == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (j == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
		buffer = _realloc(buffer, input, input + 1);
		buffer[input] = x;
		input++;
	}
	buffer[input] = '\0';
	check_line(lineptr, n, buffer, input);
	readchars = input;
	if (j != 0)
	input = 0;
	return (readchars);
}

/**
 * reads_line - reads user input
 * Description: Reads user input typed
 * @endfile: return value of getline
 *
 * Return: input
*/
char *reads_line(int *endfile)
{
	char *input = NULL;
	size_t buf = 0;

	*endfile = get_line(&input, &buf, stdin);
	return (input);
}
