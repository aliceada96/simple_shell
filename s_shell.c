#include "s_shell.h"

/**
 * free_data - free data structures
 * @arg: Argument
 *
 * Return: void
 */
void free_data(our_shell *arg)
{
	unsigned int x;

	for (x = 0; arg->_environ[x]; x++)
	{
		free(arg->_environ[x]);
	}
	free(arg->_environ);
	free(arg->pid);
}
/**
 * set_data - initialize data structure
 * @arg: data structure
 * @av: Argument variable
 *
 * Return: void
 */
void set_data(our_shell *arg, char **av)
{
	unsigned int x;

	arg->av = av;
	arg->input = NULL;
	arg->args = NULL;
	arg->status = 0;
	arg->counter = 1;

	for (x = 0; environ[x]; x++)
		;
	arg->_environ = malloc(sizeof(char *) * (x + 1));
	for (x = 0; environ[x]; x++)
	{
		arg->_environ[x] = _strdup(environ[x]);
	}
	arg->_environ[x] = NULL;
	arg->pid = _itoa(getpid());
}

/**
 * main - entry point
 * @ac: number of items in argv
 * @av: argument variable
 *
 * Return: 0 (success)
*/
int main(int ac __attribute__((unused)), char **av)
{
	our_shell arg;

	signal(SIGINT, get_sigint);
	set_data(&arg, av);
	shell_prompt(&arg);
	free_data(&arg);

	if (arg.status < 0)
		return (255);
	return (arg.status);
}
