#ifndef MAIN_H
#define MAIN_H
#define PRINTER(c) (write(STDOUT_FILENO, c, _strlen(c)))

/**###### LIBS USED ######*/

#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

/**###### environ var ######*/

extern char **environ;
char *_parse_path(char *env[], char *pat, int *flag);
char *_getenv(char *name);

/** Structures **/
/**
 * struct path_s - singly linked list of path
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node struct
 * for create path in linked list
 */
typedef struct path_s
{
	char *str;
	unsigned int len;
	struct path_s *next;
} path_t;
/**
 * struct args - arguments
 * @argc: numbers of argv
 * @argv: double pointer of strings
 *
 * Description: struct arguments
 */
typedef struct args
{
	int argc;
	char **argv;
} args_t;
/**
 * struct node_s - containt node path and length nodes
 * @path: singly linked list of path
 * @len: length of nodes in singly linked list
 *
 * Description: node path and length nodes
 */
typedef struct node_s
{
	path_t *path;
	size_t len;
} node_t;
/**
 * struct built_f - Struct built in
 * @fc: name function
 * @f: &address function call
 */
typedef struct built_f
{
	char *fc;
	int (*f)(char **argv);
} built_t;

/**
 * struct bulltin - structure for builtin cmd
 * @command: input command
 * @fun: pointer to function
 */
typedef struct  bulltin
{
	char *command;
	int (*fun)(char **line, int er);
} bul_t;

/** ####BUL FUNC #####*/

void hashtag_handle(char *buff);
int history(char *input);
int history_dis(char **cmd, int er);
int dis_env(char **cmd, int er);
int change_dir(char **cmd, int er);
int display_help(char **cmd, int er);
int echo_bul(char **cmd, int er);
void  exit_bul(char **cmd, char *input, char **argv, int c);
int print_echo(char **cmd);
void print_number(unsigned int n);
void print_number_in(int n);
node_t build_node(void);
void delete_memory(char **table, int value);
int execute(char **argv, path_t *path);
args_t split_line(char *buf);
char *read_line(void);
void free_list(path_t *head);

/**###### Built-in funcs ######*/

int (*get_built_func(char *s))(char **);
int built_exit(char **args);
int built_env(char **args);
int built_cd(char **args);
int built_help(char **args);

/**###### STRING FUNCTION ######*/

char *_strtok(char *str, const char *tok);
unsigned int check_delim(char c, const char *str);
char *_strncpy(char *dest, char *src, int n);
int _strlen(char *s);
int _putchar(char c);
int _atoi(char *s);
void _puts(char *str);
int _strcmp(char *s1, char *s2);
int _isalpha(int c);
void array_rev(char *arr, int len);
int intlen(int num);
char *estrcat(char *dest, char *src, int i);
char *_itoa(unsigned int n);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strchr(char *s, char c);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(char *str);
char *int_to_str(int count);
char *_bstrcat(char *dest, char *src);

/**###### MEMORY  MANGMENT ####*/

char *_memset(char *s, char b, unsigned int n);
void free_env(char **env);
void *fill_an_array(void *a, int el, unsigned int len);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_calloc(unsigned int nmemb, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_all(char **input, char *line);

/** Others **/
char *build(char *token, char *value);
void free_toks(char **toks);
size_t countword(char *str, char delim);
char **tokenArray(char *cmd, char *delim);
char *funkycat(char *dest, char *middle, char *src);
char *check_cwd(char *pathstr);
int exact_path(char **path, char **toks);
void print_error(char *line, int c, char **argv);
int path_cmd(char **line);

#endif /* MAIN_H */
