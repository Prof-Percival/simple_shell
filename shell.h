#ifndef _SHELL_H_
#define _SHELL_H_
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environmentemnt */
extern char **environment;
/* Global program name */
char *name;
/* Global history counter */
int history;

/**
 * struct list_shell - A new struct type defining a linked list.
 * @directory: A directory path.
 * @next: A pointer to another struct list_shell.
 */
typedef struct list_shell
{
	char *directory;
	struct list_shell *next;
} list_type;

/**
 * struct builtin_shell - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_shell
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_type;

/**
 * struct alias_shell - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_shell.
 */
typedef struct alias_shell
{
	char *name;
	char *value;
	struct alias_shell *next;
} alias_type;

/* Global aliases linked list */
alias_type *aliases;

/* Main Helpers */
ssize_t _getline(char **line_pointer, size_t *n, FILE *stream);
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_type *get_path_directory(char *path);
int execute(char **arguments, char **front);
void free_list(list_type *head);
char *_integer_to_string(int num);

/* Input Helpers */
void handle_line(char **line, ssize_t read);
void variable_replacement(char **arguments, int *exe_ret);
char *get_arguments(char *line, int *exe_ret);
int call_arguments(char **arguments, char **front, int *exe_ret);
int run_arguments(char **arguments, char **front, int *exe_ret);
int handle_arguments(int *exe_ret);
int check_arguments(char **arguments);
void free_arguments(char **arguments, char **front);
char **replace_aliases(char **arguments);

/* String functions */
int string_length(const char *s);
char *_stringcat(char *dest, const char *src);
char *_stringcat(char *dest, const char *src, size_t n);
char *_stringcopy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _string_compare(char *s1, char *s2);
int _string_compare(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_a_builtin(char *command))(char **arguments, char **front);
int shell_exit(char **arguments, char **front);
int shell_environmentironment(char **arguments, char __attribute__((__unused__)) **front);
int shell_set_environment(char **arguments, char __attribute__((__unused__)) **front);
int shell_unset_environment(char **arguments, char __attribute__((__unused__)) **front);
int shell_change_directory(char **arguments, char __attribute__((__unused__)) **front);
int shell_alias(char **arguments, char __attribute__((__unused__)) **front);
int shell_help(char **arguments, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copy_environment(void);
void free_environment(void);
char **_get_environment(const char *variable);

/* Error Handling */
int create_an_error(char **arguments, int err);
char *error_environmentironment(char **arguments);
char *error_1(char **arguments);
char *error_2_exit(char **arguments);
char *error_2_change_directory(char **arguments);
char *error_2_syntax(char **arguments);
char *error_126(char **arguments);
char *error_127(char **arguments);

/* Linkedlist Helpers */
alias_type *add_alias_end(alias_type **head, char *name, char *value);
void free_alias_list(alias_type *head);
list_type *add_node_end(list_type **head, char *directory);
void free_list(list_type *head);

void help_all(void);
void help_alias(void);
void help_change_directory(void);
void help_exit(void);
void help_help(void);
void help_environment(void);
void help_history(void);
void help_set_environment(void);
void help_unset_environment(void);

int proc_file_commands(char *file_path, int *exe_ret);
#endif /* _SHELL_H_ */
