#include "s_shell.h"
/**
 * char_swap - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *char_swap(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * _addnode - add command lines and separators
 *
 * @sep_head: separators list head
 * @cmdln_head: command line list head
 * @input: input string
 * Return: void
 */
void _addnode(separators_s **sep_head, cmd_line_s **cmdln_head, char *input)
{
	int i;
	char *line;

	input = char_swap(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_separators_end(sep_head, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_separators_end(sep_head, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = char_swap(line, 1);
		add_cmdln_end(cmdln_head, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_cmdln: command line list
 * @arg: data structure
 * Return: no return
 */
void go_next(separators_s **list_s, cmd_line_s **list_cmdln, our_shell *arg)
{
	int loop_sep;
	separators_s *ls_s;
	cmd_line_s *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_cmdln;

	while (ls_s != NULL && loop_sep)
	{
		if (arg->status == 0)
		{
			if (ls_s->sep == '&' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '|')
				ls_l = ls_l->nxt, ls_s = ls_s->nxt;
		}
		else
		{
			if (ls_s->sep == '|' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '&')
				ls_l = ls_l->nxt, ls_s = ls_s->nxt;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->nxt;
	}

	*list_s = ls_s;
	*list_cmdln = ls_l;
}

/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @arg: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(our_shell *arg, char *input)
{

	separators_s *head_s, *list_s;
	cmd_line_s *head_cmdln, *list_cmdln;
	int loop;

	head_s = NULL;
	head_cmdln = NULL;

	_addnode(&head_s, &head_cmdln, input);

	list_s = head_s;
	list_cmdln = head_cmdln;

	while (list_cmdln != NULL)
	{
		arg->input = list_cmdln->cmd_line;
		arg->args = split_line(arg->input);
		loop = exec_line(arg);
		free(arg->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_cmdln, arg);

		if (list_cmdln != NULL)
			list_cmdln = list_cmdln->nxt;
	}

	free_separators_l(&head_s);
	free_cmdln_list(&head_cmdln);

	if (loop == 0)
		return (0);
	return (1);
}
