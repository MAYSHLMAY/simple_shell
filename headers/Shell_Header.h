#ifndef _SHELL_H_
#define _SHELL_H_

#include "macros.h"
#include "lib_dirs.h"

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
 *struct info_pas - contains pseudo-arguements to pass into a function,
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
typedef struct info_pas
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
} form_t;

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
	int (*func)(form_t *);
} builtin_table;


/* toem_shloop.c */
int executable_shell(form_t *, char **);
int find_builtin(form_t *);
void find_cmd(form_t *);
void fork_cmd(form_t *);

/* toem_parser.c */
int is_cmd(form_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(form_t *, char *, char *);


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

int c_promp(form_t *);
int is_delimiter(char, char *);
int _isalpha(int);
int _atoi(char *);

int _error_atoi(char *);
void pr_erro(form_t *, char *);
int pr_int(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int shell_exit(form_t *);
int _my_current_working_cd_cmd(form_t *);


int _myhistory(form_t *);
int alias_command(form_t *);

ssize_t get_input(form_t *);
int _getline(form_t *, char **, size_t *);
void c_block(int);

void clear_info(form_t *);
void set_info(form_t *, char **);
void free_info(form_t *, int);

char *_getenv(form_t *, const char *);
int _myenv(form_t *);
int _mysetenv(form_t *);
int _myunsetenv(form_t *);
int populate_env_list(form_t *);

/* toem_getenv.c */
char **get_environ(form_t *);
int _unsetenv(form_t *, char *);
int _setenv(form_t *, char *, char *);

/* toem_history.c */
char *get_history_file(form_t *form);
int write_history(form_t *form);
int read_history(form_t *form);
int build_history_list(form_t *form, char *buf, int linecount);
int renumber_history(form_t *form);

/* toem_vars.c */
int is_chain(form_t *, char *, size_t *);
void check_chain(form_t *, char *, size_t *, size_t, size_t);
int replace_alias(form_t *);
int replace_vars(form_t *);
int replace_string(char **, char *);

/* -- lis__it -- */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

#endif
