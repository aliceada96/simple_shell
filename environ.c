#include "s_shell.h"

/**
 * cmp_env_name - compares the environment variable name
 * @envn: Environment variable name
 * @name: environment name
 * Return: int
 */
int cmp_env_name(const char *envn, const char *name)
{
	int i;

	for (i = 0; envn[i] != '='; i++)
	{
		if (envn[i] != name[i])
			return (0);
	}
	return (i + 1);
}

/**
 * _getenv - gets the environment variable
 * @name: Environment name
 * @_environ: Environment
 * Return: char
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env = NULL;
	int i, change = 0;

	for (i = 0; _environ[i]; i++)
	{
		change = cmp_env_name(_environ[i], name);
		if (change)
		{
			ptr_env = _environ[i];
			break;
		}
	}
	return (ptr_env + change);
}
/**
 * prints_env - prints the environment
 * @arg: environment to be printed
 *
 * Return: void
*/
int prints_env(our_shell *arg)
{
	int i, j;

	for (i = 0; arg->_environ[i]; i++)
	{
		for (j = 0; arg->_environ[i][j]; j++)
			;
		write(STDOUT_FILENO, arg->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	arg->status = 0;
	return (1);
}
