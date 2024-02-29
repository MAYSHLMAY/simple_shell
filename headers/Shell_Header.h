#ifndef _SHELL_H_
#define _SHELL_H_

#include "macros.h"
#include "lib_dirs.h"

/**
 * struct his_node - singly linked list
 * @num: the number field
 * @c_r: a string
 * @next: points to the next nde
 */
typedef struct his_node
{
	int num;
	char *c_r;
	struct his_node *next;
} histo_t;

/**
 *struct info_pas - contains pseudo-arguements
 *@arg: a string generated 
 *@arg_v: an array of strings generated from arg
 *@path: a string path
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code
 *@linecount_flag: if line_c
 *@fname: the program f_name
 *@env: linked list
 *@environ: custom modified
 *@history: the history nde
 *@alias: the alias nde
 *@env_changed: on if environ
 *@status: the return
 *@cmd_buf: chn
 *@cmd_buf_type: ||, &&, ;
 *@readfd: the fd
 *@histcount: line number count
 */
typedef struct info_pas
{
	char *arg;
	char **arg_v;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	histo_t *env;
	histo_t *history;
	histo_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} flex_t;

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
	int (*func)(flex_t *);
} builtin_table;



int exe_shell(flex_t *, char **);
int find_builtin(flex_t *);
void find_cmd(flex_t *);
void fork_cmd(flex_t *);

int is_cmd(flex_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(flex_t *, char *, char *);

void _error_puts(char *);
int my_putchar(char);
int _putfile_d(char c, int fd);
int _puts_filed(char *c_r, int fd);

int my_strlen(char *);
int my_strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *my_strcat(char *, char *);


char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void my_puts(char *);
int my_putchar(char);

char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

char **my_spx(char *, char *);

char *_memset(char *, char, unsigned int);
void free_string_array(char **);
void *_realloc(void *, unsigned int, unsigned int);
int free_and_null(void **);

int c_p(flex_t *);
int ch_del(char, char *);
int _isalpha(int);
int intu(char *);

int _errorintu(char *);
void pr_erro(flex_t *, char *);
int pr_int(int, int);
char *num_cv(long int, int, int);
void remove_comments(char *);

int shell_exit(flex_t *);
int _my_cd_cmd(flex_t *);


int _myhistory(flex_t *);
int alias_command(flex_t *);

ssize_t get_input(flex_t *);
int _getline(flex_t *, char **, size_t *);
void c_block(int);

void clear_info(flex_t *);
void set_info(flex_t *, char **);
void free_info(flex_t *, int);

char *my_gev(flex_t *, const char *);
int _myenv(flex_t *);
int _mysetenv(flex_t *);
int _myunsetenv(flex_t *);
int populate_env_list(flex_t *);

char **get_environ(flex_t *);
int _unsetenv(flex_t *, char *);
int _setenv(flex_t *, char *, char *);

char *get_history_file(flex_t *fm);
int write_history(flex_t *fm);
int read_history(flex_t *fm);
int build_history_list(flex_t *fm, char *buf, int linecount);
int renumber_history(flex_t *fm);

int chec(flex_t *, char *, size_t *);
void check_chain(flex_t *, char *, size_t *, size_t, size_t);
int replace_alias(flex_t *);
int replace_vars(flex_t *);
int replace_string(char **, char *);

histo_t *add_node(histo_t **, const char *, int);
histo_t *add_node_end(histo_t **, const char *, int);
size_t print_list_str(const histo_t *);
int delete_node_at_index(histo_t **, unsigned int);
void free_list(histo_t **);
size_t list_len(const histo_t *);
char **list_to_strings(histo_t *);
size_t print_list(const histo_t *);
histo_t *node_starts_with(histo_t *, char *, char);
ssize_t get_node_index(histo_t *, histo_t *);

#endif
