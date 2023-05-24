#include "s_shell.h"

/**
 * rm_comment - removes comments from the input
 * @ip: input string
 *
 * Return: input
 */
char *rm_comment(char *ip)
{
	int i, limit;

	limit = 0;
	for (i = 0; ip[i]; i++)
	{
		if (ip[i] == '#')
		{
			if (i == 0)
			{
				free(ip);
				return (NULL);
			}

			if (ip[i - 1] == ' ' || ip[i - 1] == '\t' || ip[i - 1] == ';')
				limit = i;
		}
	}

	if (limit != 0)
	{
		ip = _realloc(ip, i, limit + 1);
		ip[limit] = '\0';
	}

	return (ip);
}

/**
 * shell_prompt - loop of prompt
 * @arg: shell data
 *
 * Return: void.
 */
void shell_prompt(our_shell *arg)
{
	int prompt = 1;
	int i_eof;
	char *input;

	while (prompt == 1)
	{
		write(STDIN_FILENO, "$ ", 3);
		input = reads_line(&i_eof);
		if (i_eof != -1)
		{
			input = rm_comment(input);
			if (input == NULL)
				continue;

			if (syntax_error(arg, input) == 1)
			{
				arg->status = 2;
				free(input);
				continue;
			}
			input = replace_var(input, arg);
			prompt = split_commands(arg, input);
			arg->counter += 1;
			free(input);
		}
		else
		{
			prompt = 0;
			free(input);
		}
	}
}
