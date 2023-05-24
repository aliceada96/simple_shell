#include "s_shell.h"

/**
 * cmd_nt_found - General error msg for cmd not found
 * @arg: data being fed to the shell
 * Return: Error message
 */
char *cmd_nt_found(our_shell *arg)
{
	int l;
	char *error;
	char *ver_str;

	ver_str = _itoa(arg->counter);
	l = _strlen(arg->av[0]) + _strlen(ver_str);
	l += _strlen(arg->args[0]) + 16;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, arg->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, arg->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
