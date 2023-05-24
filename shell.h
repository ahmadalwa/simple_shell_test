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

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


/**
 * struct list-string - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct list-string
{
	int num;
	char *str;
	struct list-string *next;
} listto;

/**
 * struct pass-information - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argov:an array of strings generated from arg
 * @path: a string path for the current command
 * @argoc: the argument count
 * @linescounts: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @envirochanged: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct pass-information
{
	char *argo;
	char **argov;
	char *path;
	int argoc;
	unsigned int linescounts;
	int err_num;
	int linecount_flag;
	char *fname;
	listto *env;
	listto *history;
	listto *alias;
	char **environ;
	int envirochanged;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} (informt;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)((informt *);
} builtin_table;


/* toem_shloop.c */
int hsh((informt *, char **);
int find_builtin((informt *);
void find_cmd((informt *);
void fork_cmd((informt *);

/* toem_parser.c */
int is_cmd((informt *, char *);
char *dup_chars(char *, int, int);
char *find_path((informt *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive((informt *);
int isdlim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error((informt *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit((informt *);
int _mycd((informt *);
int _myhelp((informt *);

/* toem_builtin1.c */
int _myhistory((informt *);
int _myalias((informt *);

/*toem_getline.c */
ssize_t get_input((informt *);
int _getline((informt *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info((informt *);
void set_info((informt *, char **);
void free_info((informt *, int);

/* toem_environ.c */
char *_getenv((informt *, const char *);
int _myenv((informt *);
int _mysetenv((informt *);
int _myunsetenv((informt *);
int populate_env_list((informt *);

/* toem_getenv.c */
char **getenvir-n((informt *);
int _unsetenv((informt *, char *);
int _setenv((informt *, char *, char *);

/* toem_history.c */
char *get_history_file((informt *info);
int write_history((informt *info);
int read_history((informt *info);
int build_history_list((informt *info, char *buf, int linecount);
int renumber_history((informt *info);

/* toem_lists.c */
listto *add_node(listto **, const char *, int);
listto *add_node_end(listto **, const char *, int);
size_t print_list_str(const listto *);
int delete_node_at_index(listto **, unsigned int);
void free_list(listto **);

/* toem_lists1.c */
size_t list_len(const listto *);
char **listtostrings_strings(listto *);
size_t print_list(const listto *);
listto *node_starts_with(listto *, char *, char);
ssize_t get_node_index(listto *, listto *);

/* toem_vars.c */
int is_chain((informt *, char *, size_t *);
void check_chain((informt *, char *, size_t *, size_t, size_t);
int replace_alias((informt *);
int replace_vars((informt *);
int replace_string(char **, char *);

#endif
