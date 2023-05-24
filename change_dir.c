#include "s_shell.h"

/**
 * cd_dot - change to parent directory
 * @arg: Directory to change to
 *
 * Return: void
 */
void cd_dot(our_shell *arg)
{
	char pwd[PATH_MAX];
	char *dir, *current_pwd, *current_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	current_pwd = _strdup(pwd);
	set_env("OLDPWD", current_pwd, arg);
	dir = arg->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", current_pwd, arg);
		free(current_pwd);
		return;
	}
	if (_strcmp("/", current_pwd) == 0)
	{
		free(current_pwd);
		return;
	}
	current_strtok_pwd = current_pwd;
	rev_string(current_strtok_pwd);
	current_strtok_pwd = _strtok(current_strtok_pwd, "/");
	if (current_strtok_pwd != NULL)
	{
		current_strtok_pwd = _strtok(NULL, "\0");
		if (current_strtok_pwd != NULL)
			rev_string(current_strtok_pwd);
	}
	if (current_strtok_pwd != NULL)
	{
		chdir(current_strtok_pwd);
		set_env("PWD", current_strtok_pwd, arg);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", arg);
	}
	arg->status = 0;
	free(current_pwd);
}

/**
 * cd_home - change directory to home
 * @arg: Arguments
 *
 * Return:void
 */
void cd_home(our_shell *arg)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);
	home = _getenv("HOME", arg->_environ);
	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, arg);
		free(p_pwd);
		return;
	}
	if (chdir(home) == -1)
	{
		get_error(arg, 2);
		free(p_pwd);
		return;
	}
	set_env("OLDPWD", p_pwd, arg);
	set_env("PWD", home, arg);
	free(p_pwd);
	arg->status = 0;
}
/**
 * cd_to - Change to a specified directory
 * @arg: Arguments
 *
 * Return: void
 */
void cd_to(our_shell *arg)
{
	char pwd[PATH_MAX];
	char *dir, *current_pwd, *current_dir;

	getcwd(pwd, sizeof(pwd));
	dir = arg->args[1];
	if (chdir(dir) == -1)
	{
		get_error(arg, 2);
		return;
	}
	current_pwd = _strdup(pwd);
	set_env("PREV_PWD", current_pwd, arg);
	current_dir = _strdup(dir);
	set_env("PWD", current_dir, arg);
	free(current_pwd);
	free(current_dir);

	arg->status = 0;
	chdir(dir);
}
/**
 * cd_previous - (cd ..)Changes to the previous directory
 * @arg: Arguments
 *
 * Return: void
 */
void cd_previous(our_shell *arg)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *current_pwd, *current_oldpwd;

	getcwd(pwd, sizeof(pwd));
	current_pwd = _strdup(pwd);
	p_oldpwd = _getenv("OLDPWD", arg->_environ);
	if (p_oldpwd == NULL)
		current_oldpwd = current_pwd;
	else
		current_oldpwd  = _strdup(p_oldpwd);

	set_env("OLDPWD", current_pwd, arg);
	if (chdir(current_oldpwd) == -1)
		set_env("PWD", current_pwd, arg);
	else
		set_env("PWD", current_oldpwd, arg);

	p_pwd = _getenv("PWD", arg->_environ);
	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(current_pwd);
	if (p_oldpwd)
		free(current_oldpwd);

	arg->status = 0;
	chdir(p_pwd);
}

