#include "s_shell.h"

/**
 * get_sigint - handle the crtl + c call in prompt
 * @sig: signal handler
 *
 * Return: void
 */
void get_sigint(int sig)
{
	(void)sig;

	write(STDOUT_FILENO, "\nCtrl + c pressed ", 5);
}
