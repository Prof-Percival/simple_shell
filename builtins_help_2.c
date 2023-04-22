#include "shell.h"

void help_environment(void);
void help_history(void);
void help_set_environment(void);
void help_unset_environment(void);

/**
 * help_environment - It displays information on the shell builtin command 'env'.
 */
void help_environment(void)
{
	char *message = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * help_set_environment - It displays information on the shell builtin command 'setenv'.
 */
void help_set_environment(void)
{
	char *message = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * help_unset_environment - It displays information on the shell builtin command
 * 'unsetenv'.
 */
void help_unset_environment(void)
{
	char *message = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "message to stderr.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}
