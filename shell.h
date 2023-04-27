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
#define READ_MAS_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for number_atoi() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_nhistory"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @stri: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *stri;
	struct liststr *next;
} lists_t;

/**
 * struct passmes - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @lines_count: the error count
 * @err_code: the error code for exit()s
 * @linecount_flags: if on count this line of input
 * @fnamed: the program filenamed
 * @env: linked list local copy of environm
 * @environm: custom modified copy of environm from LL env
 * @nhistory: the nhistory node
 * @alias: the alias node
 * @envi_changed: on if environm was changed
 * @status: the return status of the last exec'd command
 * @cmd_mas: address of pointer to cmd_mas, on if chaining
 * @cmd_mas_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcounts: the nhistory line number count
 */
typedef struct passmes
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lines_count;
	int err_code;
	int linecount_flags;
	char *fnamed;
	lists_t *env;
	lists_t *nhistory;
	lists_t *alias;
	char **environm;
	int envi_changed;
	int status;

	char **cmd_mas;
	int cmd_mas_type;
	int readfd;
	int histcounts;
} mes_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct built_in - contains a built-in string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct built_in
{
	char *type;
	int (*func)(mes_t *);
} built_in_table;


int hsh(mes_t *, char **);
int find_built_in(mes_t *);
void find_cmd(mes_t *);
void fork_cmd(mes_t *);

int isit_cmd(mes_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(mes_t *, char *, char *);

int loophsh(char **);

void _printsti(char *);
int _eputchark(char);
int _putinfd(char a, int fd);
int _putsinfd(char *stri, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *start_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _putsin(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_locachr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int bfree(void **);

int _active(mes_t *);
int is_delimeter(char, char *);
int _isalphabet(int);
int _atoistring(char *);

int _erroratoi(char *);
void errprint(mes_t *, char *);
int print_base(int, int);
char *number_atoi(long int, int, int);
void func_replace(char *);

int _shellexit(mes_t *);
int _mycdir(mes_t *);
int _myhelper(mes_t *);

int _nnhistory(mes_t *);
int _myaliass(mes_t *);

ssize_t get_minus(mes_t *);
int _getlinen(mes_t *, char **, size_t *);
void siginHandler(int);

void clear_mes(mes_t *);
void set_mes(mes_t *, char **);
void free_mes(mes_t *, int);

char *_getenvi(mes_t *, const char *);
int _myenvi(mes_t *);
int _mysetenvi(mes_t *);
int _myunsetenvi(mes_t *);
int populate_envi_lists(mes_t *);

char **get_environm(mes_t *);
int _unsetenvi(mes_t *, char *);
int _setenvi(mes_t *, char *, char *);

char *get_nhistory_file(mes_t *mes);
int write_nhistory(mes_t *mes);
int read_nhistory(mes_t *mes);
int build_nhistory_list(mes_t *mes, char *mas, int linecounts);
int renumber_nhistory(mes_t *mes);

lists_t *add_node(lists_t **, const char *, int);
lists_t *added_node_end(lists_t **, const char *, int);
size_t print_lists_str(const lists_t *);
int delete_node_index(lists_t **, unsigned int);
void free_list(lists_t **);

size_t list_len(const lists_t *);
char **lists_to_strings(lists_t *);
size_t print_lists(const lists_t *);
lists_t *node_starts_prefix(lists_t *, char *, char);
ssize_t get_index_node(lists_t *, lists_t *);

int isit_chain(mes_t *, char *, size_t *);
void status_chain(mes_t *, char *, size_t *, size_t, size_t);
int replace_aliass(mes_t *);
int replace_varss(mes_t *);
int replace_string(char **, char *);

#endif

