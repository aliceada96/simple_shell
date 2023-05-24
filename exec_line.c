
#include "s_shell.h"

/**
 * exec_line - finds commands and arguments
 * @arg: arguments
 *
 * Return: int
 */
int exec_line(our_shell *arg)
{
	int (*builtin)(our_shell *arg);

	if (arg->args[0] == NULL)
		return (1);

	builtin = _builtin(arg->args[0]);

	if (builtin != NULL)
		return (builtin(arg));

	return (exec_cmd(arg));
}
