#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@error_number: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_number;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} information_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(information_t *);
} builtin_table;


/* toem_shloop.c */
int executable_shell(information_t *, char **);
int find_builtin(information_t *);
void find_cmd(information_t *);
void fork_cmd(information_t *);

/* toem_parser.c */
int is_cmd(information_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(information_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _error_puts(char *);
int _error_putchar(char);
int _putfile_d(char c, int fd);
int _puts_filed(char *str, int fd);

/* toem_string.c */
int my_strlen(char *);
int my_strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *my_strcat(char *, char *);

/* toem_string1.c */
char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void my_puts(char *);
int my_putchar(char);

/* toem_exits.c */
char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void free_string_array(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int free_and_null(void **);

/* toem_atoi.c */
int is_interactive(information_t *);
int is_delimiter(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _error_atoi(char *);
void print_error(information_t *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int shell_exit(information_t *);
int _my_current_working_cd_cmd(information_t *);
int _myhelp(information_t *);

/* toem_builtin1.c */
int _myhistory(information_t *);
int alias_command(information_t *);

/*toem_getline.c */
ssize_t get_input(information_t *);
int _getline(information_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(information_t *);
void set_info(information_t *, char **);
void free_info(information_t *, int);

/* toem_environ.c */
char *_getenv(information_t *, const char *);
int _myenv(information_t *);
int _mysetenv(information_t *);
int _myunsetenv(information_t *);
int populate_env_list(information_t *);

/* toem_getenv.c */
char **get_environ(information_t *);
int _unsetenv(information_t *, char *);
int _setenv(information_t *, char *, char *);

/* toem_history.c */
char *get_history_file(information_t *info);
int write_history(information_t *info);
int read_history(information_t *info);
int build_history_list(information_t *info, char *buf, int linecount);
int renumber_history(information_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(information_t *, char *, size_t *);
void check_chain(information_t *, char *, size_t *, size_t, size_t);
int replace_alias(information_t *);
int replace_vars(information_t *);
int replace_string(char **, char *);

#endif