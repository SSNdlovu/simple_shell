#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>

/* 4 rd/wr buffer */
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024


/* 4 comm chain */
#define CMD_CHAIN       3
#define CMD_NORM	0
#define CMD_AND         2
#define CMD_OR		1

/* 4 conv_num() */
#define CONVERT_UNSIGNED        2
#define CONVERT_LOWERCASE	1

/* 1using sys getl() */
#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_MAX        4096
#define HIST_FILE	".simple_shell_history"

extern char **environ1;


/**
 * struct liststr - 1ngly link lst
 * @num: the num
 * @str: str
 * @next: pnts the following nd
 */
typedef struct liststr
{
	struct liststr *next;
	int num;
	char *str;
} list_t;

/**
 * struct passinfo - contn pseudo intn,
 * allowie forunction pointruct
 * @arg: a sg generarom getlintaining aments
 * @argv:arr of str gen 4rm arg
 * @path: str pat comm
 * @argc: da arg cnt
 * @line_count: da err cnt
 * @err_num: da err c000de 4 et()
 * @linecount_flag: if on cnt ths linof inp
 * @fname: da prog fname
 * @env: link lt loc coy of envi
 * @environ: custm moied c
 * @history: da htory nod
 * @alias: da als nod
 * @env_changed: onif envron w chng
 * @status: da retrn sts of the last exed comma
 * @cmd_buf: add of point to cmd_bf, onif chain
 * @cmd_buf_type: C_type |or or|, and and &&, ;
 * @readfd: da fud from wch to read | inp
 * @histcount: da hstory lne num cnt
 */
typedef struct passinfo
{
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ1;
	int err_num;
	int linecount_flag;
	int status;
	int env_changed;
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;

	int readfd;
	int histcount;
	char **cmd_buf; /* pointto cmd ; chn buff, 4 mem man */
	int cmd_buf_type; /* CMD_type | or or |, & and and &, ; */
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL,\
		0, 0, 0}

/**
 * struct builtin - cins builtin str & rel func
 * @type: da builtin com flg
 * @func: da func
 */
typedef struct builtin
{
	int (*func)(info_t *);
	char *type;

} builtin_table;


/* toem_shloop.c */
void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);
int find_builtin(info_t *);

/* toem_parser.c */
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);

/* toem_string.c */
int _strlen(char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);

/* toem_string1.c */
void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);

/* toem_exits.c */
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* toem_realloc.c */
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
void ffree(char **);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);

/* toem_errors1.c */
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
void print_error(info_t *, char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _myhelp(info_t *);
int _mycd(info_t *);

/* toem_builtin11.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/*toem_getline.c */
void sigintHandler(int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);

/* toem_getinfo.c */
void free_info(info_t *, int);
void clear_info(info_t *);
void set_info(info_t *, char **);

/* toem_environ1.c */
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);

/* toem_getenv.c */
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);

/* toem_history.c */
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
char *get_history_file(info_t *info);
int write_history(info_t *info);

/* toem_lists.c */
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);

/* toem_lists1.c */
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);

/* toem_vars.c */
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

#endif

