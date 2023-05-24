#include "s_shell.h"

/**
 * exit_shell - exit shell with a given status
 * @arg:arguments
 * Return: 0
 */

int exit_shell(our_shell *arg)
{
	unsigned int exit_status;
	int num;
	int strlen;
	int exit_num;

	if (arg->args[1] != NULL)
	{
		exit_status = my_atoi(arg->args[1]);
		num = _isNumeric(arg->args[1]);
		strlen = _strlen(arg->args[1]);
		exit_num = exit_status > (unsigned int)INT_MAX;
		if (!num || strlen > 10 || exit_num)
		{
			get_error(arg, 2);
			arg->status = 2;
			return (1);
		}
		arg->status = (exit_status % 256);
	}
	return (0);
}
