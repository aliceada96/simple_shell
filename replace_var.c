#include "s_shell.h"

/**
 * replace_ip - replaces string with variables
 *
 * @head: head linked list
 * @input: input string
 * @new_input: new replaced input
 * @new_len: new length
 * Return: replaced string
 */

char *replace_ip(_var **head, char *input, char *new_input, int new_len)
{
	_var *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < new_len; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->var_len) && !(index->value_len))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (index->var_len && !(index->value_len))
			{
				for (k = 0; k < index->var_len; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->var_len; k++)
				{
					new_input[i] = index->value[k];
					i++;
				}
				j += (index->var_len);
				i--;
			}
			index = index->nxt;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * check_envn - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @arg: data structure
 * Return: no return
 */

void check_envn(_var **h, char *in, our_shell *arg)
{
	int row, chr, j, lval;
	char **envr;

	envr = arg->_environ;
	for (row = 0; envr[row]; row++)
	{
		for (j = 1, chr = 0; envr[row][chr]; chr++)
		{
			if (envr[row][chr] == '=')
			{
				lval = _strlen(envr[row] + chr + 1);
				add_var_node(h, j, envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_var_node(h, j, NULL, 0);
}

/**
 * var_check - check for  $$ or $ in typed input
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @arg: data structure
 * Return: no return
 */
int var_check(_var **h, char *in, char *st, our_shell *arg)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(arg->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_var_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_var_node(h, 2, arg->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_var_node(h, 0, NULL, 0);
			else
				check_envn(h, in + i, arg);
		}
	}

	return (i);
}

/**
 * replace_var - calls functions to replace string
 * @input: input string
 * @arg: data in our shell
 * Return: replaced string
 */
char *replace_var(char *input, our_shell *arg)
{
	_var *head, *index;
	char *status, *new_input;
	int old_len, new_len;

	status = _itoa(arg->status);
	head = NULL;

	old_len = var_check(&head, input, status, arg);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	index = head;
	new_len = 0;

	while (index != NULL)
	{
		new_len += (index->value_len - index->var_len);
		index = index->nxt;
	}

	new_len += old_len;

	new_input = malloc(sizeof(char) * (new_len + 1));
	new_input[new_len] = '\0';

	new_input = replace_ip(&head, input, new_input, new_len);

	free(input);
	free(status);
	free_var_list(&head);

	return (new_input);
}
