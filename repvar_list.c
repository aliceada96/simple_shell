#include "s_shell.h"

/**
 * add_var_node - adds a variable at the end
 * of variables list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
_var *add_var_node(_var **head, int lvar, char *val, int lval)
{
	_var *new, *temp;

	new = malloc(sizeof(_var));
	if (new == NULL)
		return (NULL);

	new->var_len = lvar;
	new->value = val;
	new->value_len = lval;

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
 * free_var_list - frees a variables list
 * @head: head of the variables list.
 * Return: no return.
 */
void free_var_list(_var **head)
{
	_var *tmp;
	_var *current;

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
