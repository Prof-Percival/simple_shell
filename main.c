#include "shell.h"

void signal_handler(int signal_value);
int execute(char **arguments, char **front);

/**
 * signal_handler - Prints a new prompt upon a signal.
 * @signal: The signal.
 */
void signal_handler(int signal_value)
{
	char *new_prompt = "\n$ ";

	(void)signal_value;
	signal(SIGINT, signal_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - Executes a command in a child process.
 * @arguments: An array of arguments.
 * @front: A double pointer to the beginning of arguments.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int execute(char **arguments, char **front)
{
	pid_t child_pid;
	int status, flag = 0, return_value = 0;
	char *command = arguments[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			return_value = (create_an_error(arguments, 126));
		else
			return_value = (create_an_error(arguments, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, arguments, environment);
			if (errno == EACCES)
				return_value = (create_an_error(arguments, 126));
			free_environment();
			free_arguments(arguments, front);
			free_alias_list(aliases);
			_exit(return_value);
		}
		else
		{
			wait(&status);
			return_value = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (return_value);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int return_value = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	history = 1;
	aliases = NULL;
	signal(SIGINT, signal_handler);

	*exe_ret = 0;
	environment = _copy_environment();
	if (!environment)
		exit(-100);

	if (argc != 1)
	{
		return_value = proc_file_commands(argv[1], exe_ret);
		free_environment();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (return_value != END_OF_FILE && return_value != EXIT)
			return_value = handle_arguments(exe_ret);
		free_environment();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		return_value = handle_arguments(exe_ret);
		if (return_value == END_OF_FILE || return_value == EXIT)
		{
			if (return_value == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_environment();
			free_alias_list(aliases);
			exit(*exe_ret);
		}
	}

	free_environment();
	free_alias_list(aliases);
	return (*exe_ret);
}
