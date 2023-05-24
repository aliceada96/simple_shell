#include "s_shell.h"

/**
 * strcat_cd_error - concatenates error message for cd error
 * @arg: Argument directory
 * @msg: message to print
 * @error: output
 * @str_count: lines counter
 *
 * Return: error
 */
char *strcat_cd_error(our_shell *arg, char *msg, char *str_count, char *error)
{
	char *wrong_value;

	_strcpy(error,  arg->args[0]);
	_strcat(error, ": ");
	_strcat(error, str_count);
	_strcat(error, ": ");
	_strcat(error, arg->args[0]);
	_strcat(error, msg);

	if (arg->args[1][0] == '-')
	{
		wrong_value = malloc(3);
		wrong_value[0] = '-';
		wrong_value[1] = arg->args[1][1];
		wrong_value[2] = '\0';
		_strcat(error, wrong_value);
		free(wrong_value);
	}
	else
	{
		_strcat(error, arg->args[1]);
	}
	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}
/**
 * get_cd_error - error trying to run change directory
 * @arg: Arguments
 *
 * Return: error
 */
char *get_cd_error(our_shell *arg)
{
	int total_length, id_length;
	char *error_msg, *ver_string, *error, *msg;

	ver_string = _itoa(arg->counter);
	if (arg->args[1][0] == '-')
	{
		msg = ":wrong option ";
		id_length = 2;
	}
	else
	{
		msg = ": no directory ";
		id_length = _strlen(arg->args[1]);
	}
	total_length = _strlen(arg->av[0]) + _strlen(arg->args[0]);
	total_length += _strlen(ver_string) + _strlen(msg) + id_length + 5;

	error_msg = malloc(sizeof(char) * (total_length + 1));
	if (error_msg == 0)
	{
		free(ver_string);
		return (NULL);
	}
	error = strcat_cd_error(arg, msg, error_msg, ver_string);
	free(ver_string);
	return (error);
}
/**
 * not_found_error - error message for command not found
 * @arg: Argument
 * Return: error
*/
char *not_found_error(our_shell *arg)
{
	int length;
	char *ver_string, *error;

	ver_string = _itoa(arg->counter);
	length = _strlen(arg->av[0]) + _strlen(ver_string);
	length += _strlen(arg->args[0]) + 16;

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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_string);
	return (error);
}


/**
 * exit_shell_error - error when exiting shell
 * @arg:Arguments
 *
 * Return: error
 */
char *exit_shell_error(our_shell *arg)
{
	int length;
	char *ver_string, *error;

	ver_string = _itoa(arg->counter);
	length = _strlen(arg->av[0]) + _strlen(ver_string);
	length += _strlen(arg->args[0]) + _strlen(arg->args[1]) + 23;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_string);
		return (NULL);
	}
	_strcpy(error, arg->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_string);
	_strcat(error, ": ");
	_strcat(error, arg->args[0]);
	_strcat(error, ":wrong number: ");
	_strcat(error, arg->args[1]);
	_strcat(error, "\n\0");
	free(ver_string);
	return (error);
}
