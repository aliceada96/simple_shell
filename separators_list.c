#include "s_shell.h"

/**
 * add_cmdln_end - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @cmd_line: command line.
 * Return: address of the head.
 */
cmd_line_s *add_cmdln_end(cmd_line_s **head, char *cmd_line)
{
	cmd_line_s *new, *tmp;

	new = malloc(sizeof(cmd_line_s));
	if (new == NULL)
		return (NULL);

	new->cmd_line = cmd_line;
	new->nxt = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->nxt != NULL)
			tmp = tmp->nxt;
		tmp->nxt = new;
	}

	return (*head);
}

/**
 * free_cmdln_list - frees a command line list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_cmdln_list(cmd_line_s **head)
{
	cmd_line_s *tmp;
	cmd_line_s *current;

	if (head != NULL)
	{
		current = *head;
		while ((tmp = current) != NULL)
		{
			current = current->nxt;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * add_separators_end - adds a separator found at the end
 * of a separators list
 * @head: head of the linked list.
 * @separator: separator found (; | &).
 * Return: address of the head.
 */
separators_s *add_separators_end(separators_s **head, char separator)
{
	separators_s *new, *temp;

	new = malloc(sizeof(separators_s));
	if (new == NULL)
		return (NULL);

	new->sep = separator;
	new->nxt = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->nxt != NULL)
			temp = temp->nxt;
		temp->nxt = new;
	}

	return (*head);
}

/**
 * free_separators_l - frees a separators linked list
 * @head: head of the linked list.
 * Return: void
 */
void free_separators_l(separators_s **head)
{
	separators_s *tmp;
	separators_s *current;

	if (head != NULL)
	{
		current = *head;
		while ((tmp = current) != NULL)
		{
			current = current->nxt;
			free(tmp);
		}
		*head = NULL;
	}
}
