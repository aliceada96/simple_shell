#include "s_shell.h"

/**
 * copies_info - gets/copies information
 * @name: Name
 * @value: Value
 * Return: new
 */
char *copies_info(char *name, char *value)
{
	char *new;
	int len, len_name, len_value;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;

	new = malloc(sizeof(char) * len);
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}
/**
 * set_env - sets the environment variable
 * @name: environment name
 * @value: environment value
 * @arg: Argument
 *
 * Return: void
 */
void set_env(char *name, char *value, our_shell *arg)
{
	int x;
	char *name_env, *var_name;

	for (x = 0; arg->_environ[x]; x++)
	{
		name_env = _strtok(var_name, "=");
		var_name = _strdup(arg->_environ[x]);
		if (_strcmp(name_env, name) == 0)
		{
			free(arg->_environ[x]);
			arg->_environ[x] = copies_info(name_env, value);
			free(var_name);
			return;
		}
		arg->_environ = _reallocdptr(arg->_environ, x, sizeof(char *) * (x + 2));
		arg->_environ[x] = copies_info(name_env, value);
		arg->_environ[x + 1] = NULL;
	}
}

/**
 * _setenv - compares environment variables  passed
 * @arg: Argument passed
 * Return: 1
 */
int _setenv(our_shell *arg)
{
	if (arg->args[1] == NULL || arg->args[2] == NULL)
	{
		get_error(arg, -1);
		return (1);
	}

	set_env(arg->args[1], arg->args[2], arg);
	return (1);
}

/**
 * _unsetenv - creates a new env variable
 * @arg: Arguments
 * Return: int
*/
int _unsetenv(our_shell *arg)
{
	char **new_environ;
	char *env_name, *env_var;
	int l, m, n;

	if (arg->args[1] == NULL)
	{
		get_error(arg, -1);
		return (1);
	}
	n = -1;
	for (l = 0; arg->_environ[l]; l++)
	{
		env_var = _strdup(arg->_environ[l]);
		env_name = _strtok(env_var, "=");

		if (_strcmp(env_name, arg->args[1]) == 0)
		{
			n = l;
		}
		free(env_var);
	}
	if (n == -1)
	{
		get_error(arg, -1);
		return (1);
	}
	new_environ = malloc(sizeof(char *) * (l));
	for (l = m = 0; arg->_environ[l]; l++)
	{
		if (l != m)
		{
			new_environ[m] = arg->_environ[l];
			m++;
		}
	}
	new_environ[m] = NULL;
	free(arg->_environ[n]);
	free(arg->_environ);
	arg->_environ = new_environ;
	return (1);
}
