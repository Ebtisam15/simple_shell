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

#define READ_M_SIZE 1024
#define WRITE_M_SIZE 1024
#define M_FLUSH -1

#define CMD_NORMAL 0
#define CMD_ORM	1
#define CMD_ANDM	2
#define CMD_CHAIM 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED  2

#define USEget_next_line 1
#define USE_STRTOK  2

#define HISTOR_FILE ".our_history_file"
#define HISTOR_MAX	4096

extern char **environm;

/**
 * struct liststri - singly linked list
 * @a: the sber field
 * @stri: a string
 * @next: points to the next node
 */
typedef struct liststri
{
	int a;
	char *stri;
	struct liststri *next;
} lists_t;

/**
 * struct passmes - contains pseudo-arguments to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @argi: a string generated from get line containing arguments
 * @argv:an array of strings generated from argi
 * @npath: a string npath for the current command
 * @argc: the argument count
 * @count: the error count
 * @err_s: the error code for exit()s
 * @count_this_line: if on count this line of input
 * @filen: the program filename
 * @envi: linked list local copy of environ
 * @environm: custom modified copy of environ from LL env
 * @nhistory: the history node
 * @nalias: the alias node
 * @envi_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_m: address of pointer to cmd_m, on if chaining
 * @cmd_m_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @historyscount: the history line sber count
 */
typedef struct passmes
{
	char *argi;
	char **argv;
	char *npath;
	int argc;
	unsigned int count;
	int err_s;
	int count_this_line;
	char *filen;
	lists_t *envi;
	lists_t *nhistory;
	lists_t *nalias;
	char **environm;
	int envi_changed;
	int status;
	char **cmd_m;
	int cmd_m_type;
	int readfd;
	int historyscount;
} mes_t;

#define MESS_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct built_in - contains a builtin string and related function
 * @typef: the builtin command flag
 * @func: the function
 */
typedef struct built_in
{
	char *typef;
	int (*func)(mes_t *);
} builtin_tables;

int active(mes_t *);
int unique_ch(char, char*);
int alphabet(int);
int _atoi(char *);

int main(int, char**);

int exe_cmd(mes_t*, char*);
char *dup_chars(char*, int, int);
char *find_npath(mes_t*, char*, char*);

int _sprint(char);
void sprint(char *);
int _sprintfd(char, int);
int _printsfd(char*, int);

char *needle_start_with(const char*, const char*);
char *dup_string(const char *);
void _instr(char *);
int _putchar(char);

int terminate(mes_t *);
int _ccd(mes_t *);
int _ccdpro(mes_t *);

int intatoi(char *);
int intbase(int, int);
void ermes(mes_t*, char*);
char *confun(long int, int, int);
void funrep(char *);

char **string_into(char*, char*);
char **string_into2(char*, char);

int chain_delim(mes_t*, char*, size_t*);
void chain_status(mes_t*, char*, size_t*, size_t, size_t);
int replace_aliases(mes_t *);
int replace_var(mes_t *);
int re_string(char**, char*);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *locate_xter(char *, char);

int historylist(mes_t *);
int unalias_string(mes_t*, char*);
int alias_string(mes_t*, char*);
int wtire_alias(lists_t *);
int copy_alias(mes_t *);

int _curenv(mes_t *);
char *envar(mes_t*, const char*);
int new_env(mes_t *);
int re_env(mes_t *);
int calculate_env_list(mes_t *);

char **str_copy_env(mes_t *);
int rem_env_var(mes_t*, char*);
int newen(mes_t*, char*, char*);

void clear_mes(mes_t *);
void set_mes(mes_t*, char**);
void free_mes(mes_t*, int);

ssize_t enter_buff(mes_t*, char**, size_t*);
ssize_t line_without_new(mes_t *);
ssize_t read_m(mes_t*, char*, size_t*);
int get_next_line(mes_t*, char**, size_t*);
void block_ctrl_c(int);

char *ghistory_file(mes_t *);
int append_file(mes_t *);
int read_nhistory(mes_t *);
int add_entry_history(mes_t*, char*, int);
int resber_history(mes_t *);

size_t lists_len(const lists_t *);
char **lists_to_strings(lists_t *);
size_t write_list(const lists_t *);
lists_t *return_node_with(lists_t*, char*, char);
ssize_t locate_index_node(lists_t*, lists_t*);

int hsh(mes_t*, char**);
int find_builtinc(mes_t *);
void find_cmdp(mes_t *);
void run_cmd(mes_t *);

int _strcmp(char*, char*);
char *_strcat(char*, char*);
int _strlen(char *);
char *_strcpy(char*, char*);

lists_t *add_anode(lists_t**, const char*, int);
lists_t *node_at_end(lists_t**, const char*, int);
size_t print_str_ele(const lists_t *);
int node_deletion(lists_t**, unsigned int);
void free_lists(lists_t **);

int bfrees(void **);

char *mem_cbytes(char*, char, unsigned int);
void ffrees(char **);
void *_reallocblock(void*, unsigned int, unsigned int);

#endif
