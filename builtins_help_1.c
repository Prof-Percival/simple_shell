#include "shell.h"

void help_all(void);
void help_alias(void);
void help_exit(void);
void help_help(void);
void help_change_directory(void);

/**
 * help_all - It displays all possible builtin shell commands.
 */
void help_all(void)
{
	char *message = "Shell\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, message, string_length(message));
	message = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, message, string_length(message));
	message = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, message, string_length(message));
	message = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, message, string_length(message));
	message = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, message, string_length(message));
	message = "\n  setenv  \tsetenv [variable] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, message, string_length(message));
	message = "unsetenv [variable]\n";
	write(STDOUT_FILENO, message, string_length(message));
}

/**
 * help_alias - It displays information on the shell builtin command 'alias'.
 */
void help_alias(void)
{
	char *message = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, message, string_length(message));
	message = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, message, string_length(message));
	message = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, message, string_length(message));
	message = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, message, string_length(message));
	message = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, message, string_length(message));
	message = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, message, string_length(message));
	message = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, message, string_length(message));
}

/**
 * help_exit - it displays information on the shell builtin command 'exit'.
 */
void help_exit(void)
{
	char *message = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, message, string_length(message));
	message = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, message, string_length(message));
	message = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, message, string_length(message));
	message = " exit 0.\n";
	write(STDOUT_FILENO, message, string_length(message));
}

/**
 * help_help - It displays information on the shell builtin command 'help'.
 */
void help_help(void)
{
	char *message = "help: help\n\tSee all possible Shell builtin commands.\n";

	write(STDOUT_FILENO, message, string_length(message));
	message = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, message, string_length(message));
	message = "builtin command.\n";
	write(STDOUT_FILENO, message, string_length(message));
}


/**
 * help_change_directory - It displays information on the shell builtin command 'cd'.
 */
void help_change_directory(void)
{
	char *message = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, message, string_length(message));
	message = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, message, string_length(message));
	message = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, message, string_length(message));
	message = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, message, string_length(message));
	message = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, message, string_length(message));
	message = "after a change of directory.\n";
	write(STDOUT_FILENO, message, string_length(message));
}
