#include "s_shell.h"

/**
 * path_126_error - error message and denied access
 * @arg: Argument
 *
 * Return: error
 */
char *path_126_error(our_shell *arg)
{
	int length;
	char *ver_string, *error;

	ver_string = _itoa(arg->counter);
	length = _strlen(arg->av[0] + _strlen(ver_string));
	length += _strlen(arg->args[0]) + 24;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_string);
		return (NULL);
	}
	_strcpy(error, arg->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_string);
	_strcat(error, ": ");
	_strcat(error, arg->args[0]);
	_strcat(error, ":Access denied\n");
	_strcat(error, "\0");
	free(ver_string);
	return (error);
}

/**
 * env_error - error msg in the environment
 * @arg: Arguments
 *
 * Return: error
 */
char *env_error(our_shell *arg)
{
	int length;
	char *error, *msg, *ver_string;

	ver_string = _itoa(arg->counter);
	msg = "Can't  add/remove from env\n";
	length = _strlen(arg->av[0]) + _strlen(ver_string);
	length += _strlen(arg->args[0]) + _strlen(msg) + 4;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_string);
		return (NULL);
	}
	_strcpy(error, arg->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_string);
	_strcat(error, ": ");
	_strcat(error, arg->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_string);
	return (error);
}
