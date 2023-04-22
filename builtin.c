#include "shell.h"
int shell_exit(char **arguments, char **front);
int (*get_a_builtin(char *command))(char **arguments, char **front);
int shell_help(char **arguments, char __attribute__((__unused__)) **front);
int shell_change_directory(char **arguments, char __attribute__((__unused__)) **front);

/**
 * shell_exit - It causes normal process termination
 *                for the shell shell.
 * @arguments: An array of arguments containing the exit value.
 * @front: A double pointer to the beginning of arguments.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int shell_exit(char **arguments, char **front)
{
	int i, length_of_integer = 10;
	unsigned int number = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (arguments[0])
	{
		if (arguments[0][0] == '+')
		{
			i = 1;
			length_of_integer++;
		}
		for (; arguments[0][i]; i++)
		{
			if (i <= length_of_integer && arguments[0][i] >= '0' && arguments[0][i] <= '9')
				number = (number * 10) + (arguments[0][i] - '0');
			else
				return (create_an_error(--arguments, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (number > max - 1)
		return (create_an_error(--arguments, 2));
	arguments -= 1;
	free_arguments(arguments, front);
	free_environment();
	free_alias_list(aliases);
	exit(number);
}

/**
 * get_a_builtin - It matches a command with a corresponding
 *               shell builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_a_builtin(char *command))(char **arguments, char **front)
{
	builtin_type functions[] = {
		{ "exit", shell_exit },
		{ "env", shell_environment },
		{ "setenv", shell_set_environment },
		{ "unsetenv", shell_unset_environment },
		{ "cd", shell_change_directory },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; functions[i].name; i++)
	{
		if (_string_compare(functions[i].name, command) == 0)
			break;
	}
	return (functions[i].f);
}


/**
 * shell_help - It displays information about shell builtin commands.
 * @arguments: An array of arguments.
 * @front: A pointer to the beginning of arguments.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_help(char **arguments, char __attribute__((__unused__)) **front)
{
	if (!arguments[0])
		help_all();
	else if (_string_compare(arguments[0], "alias") == 0)
		help_alias();
	else if (_string_compare(arguments[0], "cd") == 0)
		help_change_directory();
	else if (_string_compare(arguments[0], "exit") == 0)
		help_exit();
	else if (_string_compare(arguments[0], "env") == 0)
		help_environment();
	else if (_string_compare(arguments[0], "setenv") == 0)
		help_set_environment();
	else if (_string_compare(arguments[0], "unsetenv") == 0)
		help_unset_environment();
	else if (_string_compare(arguments[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, string_length(name));

	return (0);
}

/**
 * shell_change_directory - It changes the current directory of the shell process.
 * @arguments: An array of arguments.
 * @front: A double pointer to the beginning of arguments.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_change_directory(char **arguments, char __attribute__((__unused__)) **front)
{
	char **directory_information, *new_line = "\n";
	char *oldprint_working_directory = NULL, *print_working_directory = NULL;
	struct stat dir;

	oldprint_working_directory = getcwd(oldprint_working_directory, 0);
	if (!oldprint_working_directory)
		return (-1);

	if (arguments[0])
	{
		if (*(arguments[0]) == '-' || _string_compare(arguments[0], "--") == 0)
		{
			if ((arguments[0][1] == '-' && arguments[0][2] == '\0') ||
					arguments[0][1] == '\0')
			{
				if (_get_environment("OLDPWD") != NULL)
					(chdir(*_get_environment("OLDPWD") + 7));
			}
			else
			{
				free(oldprint_working_directory);
				return (create_an_error(arguments, 2));
			}
		}
		else
		{
			if (stat(arguments[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(arguments[0]);
			else
			{
				free(oldprint_working_directory);
				return (create_an_error(arguments, 2));
			}
		}
	}
	else
	{
		if (_get_environment("HOME") != NULL)
			chdir(*(_get_environment("HOME")) + 5);
	}

	print_working_directory = getcwd(print_working_directory, 0);
	if (!print_working_directory)
		return (-1);

	directory_information = malloc(sizeof(char *) * 2);
	if (!directory_information)
		return (-1);

	directory_information[0] = "OLDPWD";
	directory_information[1] = oldprint_working_directory;
	if (shell_set_environment(directory_information, directory_information) == -1)
		return (-1);

	directory_information[0] = "PWD";
	directory_information[1] = print_working_directory;
	if (shell_set_environment(directory_information, directory_information) == -1)
		return (-1);
	if (arguments[0] && arguments[0][0] == '-' && arguments[0][1] != '-')
	{
		write(STDOUT_FILENO, print_working_directory, string_length(print_working_directory));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldprint_working_directory);
	free(print_working_directory);
	free(directory_information);
	return (0);
}