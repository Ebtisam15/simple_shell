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
#define M_FLUSH      1

#define CMD_NORMAL 0	
#define CMD_OR	1	
#define CMD_AND	2	
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1	
#define CONVERT_UNSIGNED  2	

#define USEget_next_line 1
#define USE_STRTOK  2

#define HISTOR_FILE  ".our_history_file"   
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

int active(mes_t *mes);
int unique_ch(char u, char *unique);
int alphabet(int a);
int _atoi(char *a);

int main(int acount, char **ave);

int exe_cmd(mes_t *mes, char *npath);
char *dup_chars(char *npathstr, int starti, int stopi);
char *find_npath(mes_t *mes, char *npathstr, char *cmdf);

int _sprint(char k);
void sprint(char *h);
int _sprintfd(char k, int fd);
int _printsfd(char *h, int fd);

char *needle_start_with(const char *haystack, const char *needle);
char *dup_string(const char *str);
void _instr(char *str);
int _putchar(char);

int terminate(mes_t *mes);
int _ccd(mes_t *mes);
int _ccdpro(mes_t *mes);

int intatoi(char *a);
int intbase(int o, int fd);
void ermes(mes_t *mes, char *sh);
char *confun(long int s, int u, int t);
void funrep(char *m);

char **string_into(char *stri, char *ds);
char **string_into2(char *stri, char ds);

int chain_delim(mes_t *mes, char *m, size_t *pm);
void chain_status(mes_t *mes, char *m, size_t *pm, size_t l, size_t lm);
int replace_aliases(mes_t *mes);
int replace_var(mes_t *mes);
int re_string(char **olds, char *news);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *locate_xter(char *, char);

int historylist(mes_t *mes);
int unalias_string(mes_t *mes, char *stri);
int alias_string(mes_t *mes, char *stri);
int wtire_alias(lists_t *anode);
int copy_alias(mes_t *mes);

int _curenv(mes_t *mes);
char *envar(mes_t *mes, const char *ename);
int new_env(mes_t *mes);
int re_env(mes_t *mes);
int calculate_env_list(mes_t *mes);

char **str_copy_env(mes_t *mes);
int rem_env_var(mes_t *mes, char *env_var);
int newen(mes_t *mes, char *env_var, char *env_value);

void clear_mes(mes_t *mes);
void set_mes(mes_t *mes, char **ave);
void free_mes(mes_t *mes, int fall);

ssize_t enter_buff(mes_t *mes, char **m, size_t *ladd);
ssize_t line_without_new(mes_t *mes);
ssize_t read_m(mes_t *mes, char *m, size_t *l);
int get_next_line(mes_t *mes, char **ptri, size_t *ptr_m);
void block_ctrl_c(__attribute__((unused))int signal_s);

char *ghistory_file(mes_t *mes);
int append_file(mes_t *mes);
int read_nhistory(mes_t *mes);
int add_entry_history(mes_t *mes, char *m, int linecounts);
int resber_history(mes_t *mes);

size_t lists_len(const lists_t *nh);
char **lists_to_strings(lists_t *nhead);
size_t write_list(const lists_t *nh);
lists_t *return_node_with(lists_t *anode, char *sprefix, char nc);
ssize_t locate_index_node(lists_t *nhead, lists_t *anode);

int hsh(mes_t *mes, char **ave);
int find_builtinc(mes_t *mes);
void find_cmdp(mes_t *mes);
void run_cmd(mes_t *mes);

int _strcmp(char *, char *);
char *_strcat(char *, char *);
int _strlen(char*);
char *_strcpy(char *, char *);

lists_t *add_anode(lists_t **nhead, const char *stri, int a);
lists_t *node_at_end(lists_t **nhead, const char *stri, int a);
size_t print_str_ele(const lists_t *nh);
int node_deletion(lists_t **nhead, unsigned int nindex);
void free_lists(lists_t **nhead_ptr);

int bfrees(void **ptri);

char *mem_cbytes(char *a, char nb, unsigned int ab);
void ffrees(char **sos);
void *_reallocblock(void *ptri, unsigned int old_bsize, unsigned int new_bsize);

#endif
