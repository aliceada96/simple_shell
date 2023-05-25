#include "s_shell.h"
/**
 * cd_shell- changes directory
 * @arg: Arguments
 *
 * Return: int
 */
int cd_shell(our_shell *arg)
{
	char *dir;
	int home = 0;
	int home2 = 0;
	int doubledash = 0;

	dir = arg->args[1];
	if (dir != NULL)
	{
		home = _strcmp("$HOME", dir);
		home2 = _strcmp("~", dir);
		doubledash = _strcmp("--", dir);
	}
	else if (dir == NULL || !home || !home2 || !doubledash)
	{
		cd_home(arg);
		return (1);
	}
	else if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(arg);
		return (1);
	}
	else if (_strcmp("-", dir) == 0)
	{
		cd_previous(arg);
		return (1);
	}
	else
	{
		cd_to(arg);
		return (1);
	}
	return (0);
}
