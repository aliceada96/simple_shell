#include "s_shell.h"

/**
 * get_error - returns error according to builtin
 * @arg: Argument
 * @error_value: error value
 *
 * Return: error
 */
int get_error(our_shell *arg, int error_value)
{
	char *error;

	switch (error_value)
	{
	case -1:
		error = env_error(arg);
		break;
	case 126:
		error = path_126_error(arg);
		break;
	case 127:
		error = not_found_error(arg);
		break;
	case 2:
		if (_strcmp("exit", arg->args[0]) == 0)
			error = exit_shell_error(arg);
		else if (_strcmp("cd", arg->args[0]) == 0)
			error = get_cd_error(arg);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	arg->status = error_value;
	return (error_value);
}
