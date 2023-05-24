#ifndef S_SHELL_H
#define S_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stddef.h>
#include <string.h>


#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

int access(const char *path, int mode);
int execve(const char *path, char *const argv[], char *const envp[]);

/**
 * struct alin  - struct that contains all relevant data on runtime
 * @av: argument variable
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: line counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct alin
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} our_shell;

/**
 * struct separators_l - sepaators linked list
 * @sep: ; | &
 * @nxt: next node
 * Description: a singly linked list for storing separators
 */
typedef struct separators_l
{
	char sep;
	struct separators_l *nxt;
} separators_s;

/**
 * struct cmd_line_l - command lines linked list
 * @cmd_line: command lines
 * @nxt: next node
 * Description: a singly linked list for storing command lines
 */
typedef struct cmd_line_l
{
	char *cmd_line;
	struct cmd_line_l *nxt;
} cmd_line_s;

/**
 * struct var_list - variables linked list
 * @var_len: length of variable
 * @value: variable value
 * @value_len: value length
 * @nxt: next node
 * Description: singly linked list for storing variables
 */
typedef struct var_list
{
	int var_len;
	char *value;
	int value_len;
	struct var_list *nxt;
} _var;

/**
 * struct builtin_s - linked list of builtin cmds
 * @name:name of arguments
 * @func_ptr: function pointer
 * Description: singly linked list for storing builtin cmds
 */

typedef struct builtin_s
{
	char *name;
	int (*func_ptr)(our_shell *arg);
} builtin_t;

/**functions.c**/
int my_atoi(char *str);
char *_itoa(int n);
int get_len(int n);

/**str_functions*/
int _strlen(const char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *s);
char *_strcat(char *dest, const char *src);
int _strcmp(char *str1, char *str2);

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _isNumeric(const char *s);

void rev_string(char *s);

/**builtin functions*/
int (*_builtin(char *cmd))(our_shell *);

/**s_shell.c**/
int main(int ac __attribute__((unused)), char **av);
void set_data(our_shell *arg, char **av);
void free_data(our_shell *arg);

/**exit shell*/
int exit_shell(our_shell *arg);
/**get help*/
int get_help(our_shell *arg);

/**error.c**/
int get_error(our_shell *arg, int error_value);

/**signal.h**/
void get_sigint(int sig);

/**getline*/
void check_line(char **lineptr, size_t *n, char *buff, size_t i);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
char *reads_line(int *endfile);

/**exec_cmd.c**/
int is_current_dir(char *path, int *i);
char *_locate(char *cmd, char **_environ);
int is_executable(our_shell *arg);
int cmd_check_error(char *dir, our_shell *arg);
int exec_cmd(our_shell *arg);

/**exec_line*/
int exec_line(our_shell *arg);

/**help prototypes*/
void var_help_env(void);
void var_help_exit(void);
void var_help_setenv(void);
void var_help_unsetenv(void);

/**var_help**/
void var_help(void);
void var_help_cd(void);
void var_help_alias(void);
void var_help_general(void);

/**change_dir**/
void cd_home(our_shell *arg);
void cd_to(our_shell *arg);
void cd_previous(our_shell *arg);
int cd_shell(our_shell *arg);


/**environ**/
int cmp_env_name(const char *envn, const char *name);
char *_getenv(const char *name, char **_environ);
int prints_env(our_shell *arg);

/*environ2*/
char *copies_info(char *name, char *value);
void set_env(char *name, char *value, our_shell *arg);
int _setenv(our_shell *arg);
int _unsetenv(our_shell *arg);

/**handle_errors**/
char *get_cd_error(our_shell *arg);
char *strcat_cd_error(our_shell *arg, char *msg, char *str_count, char *error);
char *not_found_error(our_shell *arg);
char *exit_shell_error(our_shell *arg);
char *path_126_error(our_shell *arg);
char *env_error(our_shell *arg);

/**syntax eroors*/
int index_char1(char *input, int *i);
int dup_char(char *input, int i);
int error_finder(char *input, int i, char last);
void p_error(our_shell *arg, char *input, int i, int bool);
int syntax_error(our_shell *args, char *input);

/**mem_alloc**/
void mem_copy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdptr(char **ptr, unsigned int old_size, unsigned int new_size);

/**prompt**/
char *rm_comment(char *ip);
void shell_prompt(our_shell *arg);

/**token_func**/
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
char **split_line(char *input);

/** separators*/
cmd_line_s *add_cmdln_end(cmd_line_s **head, char *line);
void free_cmdln_list(cmd_line_s **head);
separators_s *add_separators_end(separators_s **head, char sep);
void free_separators_l(separators_s **head);

char *char_swap(char *input, int bool);
void _addnode(separators_s **sep_head, cmd_line_s **cmdln_head, char *input);
void go_next(separators_s **list_s, cmd_line_s **list_cmdln, our_shell *arg);
int split_commands(our_shell *arg, char *input);

/** replace_var*/
char *replace_ip(_var **head, char *input, char *new_input, int new_len);
void check_envn(_var **h, char *in, our_shell *arg);
int var_check(_var **h, char *in, char *st, our_shell *arg);
char *replace_var(char *input, our_shell *arg);

_var *add_var_node(_var **head, int lvar, char *val, int lval);
void free_var_list(_var **head);

#endif
