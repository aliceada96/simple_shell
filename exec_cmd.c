#include "s_shell.h"
/**
 * is_current_dir - checks ":" if is in the current directory
 * @path: type char pointer char
 * @i: type int pointer of index
 * Return: 1 if the path is searchable in the cd, 0 otherwise
 */
int is_current_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _locate - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command
 */
char *_locate(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_current_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if is an executable
 * struct stat st - stores file info retrieved
 * @arg: data structure
 * Return: 0 if executable else other no
 */
int is_executable(our_shell *arg)
{
	struct stat st;/*store file information retrieved*/
	int i;
	char *input;

	input = arg->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_error(arg, 127);
	return (-1);
}

/**
 * cmd_check_error - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @arg: argument
 * Return: 1 error, 0 if not
 */
int cmd_check_error(char *dir, our_shell *arg)
{
	if (dir == NULL)
	{
		get_error(arg, 127);
		return (1);
	}
/*unistd function X_OK checks for executable permission*/
	if (_strcmp(arg->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(arg, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(arg->args[0], X_OK) == -1)
		{
			get_error(arg, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * exec_cmd - executes command lines
 * @arg: Arguments
 * Return: 1
 */
int exec_cmd(our_shell *arg)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable(arg);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _locate(arg->args[0], arg->_environ);
		if (cmd_check_error(dir, arg) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _locate(arg->args[0], arg->_environ);
		else
			dir = arg->args[0];
		execve(dir + exec, arg->args, arg->_environ);
	}
	else if (pd < 0)
	{
		perror(arg->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	arg->status = state / 256;
	return (1);
}
