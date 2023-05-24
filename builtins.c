#include "s_shell.h"

/**
 * _builtin - linked list containing all built in cmds
 * @cmd: Command typed
 * Return: pointer to builtin command
 */

int (*_builtin(char *cmd))(our_shell *)
{
	builtin_t builtin[] = {
		{ "env", prints_env },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "exit", exit_shell },
		{ "cd", cd_shell },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].func_ptr);
}
