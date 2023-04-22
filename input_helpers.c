#include "shell.h"

char *get_arguments(char *line, int *exe_ret);
int call_arguments(char **arguments, char **front, int *exe_ret);
int handle_arguments(int *exe_ret);
int check_arguments(char **arguments);
int run_arguments(char **arguments, char **front, int *exe_ret);

/**
 * get_arguments - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurrents - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_arguments(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		history++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_arguments(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_arguments - Partitions operators from commands and calls them.
 * @arguments: An array of arguments.
 * @front: A double pointer to the beginning of arguments.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_arguments(char **arguments, char **front, int *exe_ret)
{
	int return_value, index;

	if (!arguments[0])
		return (*exe_ret);
	for (index = 0; arguments[index]; index++)
	{
		if (_string_compare(arguments[index], "||", 2) == 0)
		{
			free(arguments[index]);
			arguments[index] = NULL;
			arguments = replace_aliases(arguments);
			return_value = run_arguments(arguments, front, exe_ret);
			if (*exe_ret != 0)
			{
				arguments = &arguments[++index];
				index = 0;
			}
			else
			{
				for (index++; arguments[index]; index++)
					free(arguments[index]);
				return (return_value);
			}
		}
		else if (_string_compare(arguments[index], "&&", 2) == 0)
		{
			free(arguments[index]);
			arguments[index] = NULL;
			arguments = replace_aliases(arguments);
			return_value = run_arguments(arguments, front, exe_ret);
			if (*exe_ret == 0)
			{
				arguments = &arguments[++index];
				index = 0;
			}
			else
			{
				for (index++; arguments[index]; index++)
					free(arguments[index]);
				return (return_value);
			}
		}
	}
	arguments = replace_aliases(arguments);
	return_value = run_arguments(arguments, front, exe_ret);
	return (return_value);
}

/**
 * handle_arguments - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_arguments(int *exe_ret)
{
	int return_value = 0, index;
	char **arguments, *line = NULL, **front;

	line = get_arguments(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	arguments = _strtok(line, " ");
	free(line);
	if (!arguments)
		return (return_value);
	if (check_arguments(arguments) != 0)
	{
		*exe_ret = 2;
		free_arguments(arguments, arguments);
		return (*exe_ret);
	}
	front = arguments;

	for (index = 0; arguments[index]; index++)
	{
		if (_string_compare(arguments[index], ";", 1) == 0)
		{
			free(arguments[index]);
			arguments[index] = NULL;
			return_value = call_arguments(arguments, front, exe_ret);
			arguments = &arguments[++index];
			index = 0;
		}
	}
	if (arguments)
		return_value = call_arguments(arguments, front, exe_ret);

	free(front);
	return (return_value);
}

/**
 * check_arguments - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @arguments: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_arguments(char **arguments)
{
	size_t i;
	char *current, *nex;

	for (i = 0; arguments[i]; i++)
	{
		current = arguments[i];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (i == 0 || current[1] == ';')
				return (create_an_error(&arguments[i], 2));
			nex = arguments[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_an_error(&arguments[i + 1], 2));
		}
	}
	return (0);
}


/**
 * run_arguments - Calls the execution of a command.
 * @arguments: An array of arguments.
 * @front: A double pointer to the beginning of arguments.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_arguments(char **arguments, char **front, int *exe_ret)
{
	int return_value, i;
	int (*builtin)(char **arguments, char **front);

	builtin = get_a_builtin(arguments[0]);

	if (builtin)
	{
		return_value = builtin(arguments + 1, front);
		if (return_value != EXIT)
			*exe_ret = return_value;
	}
	else
	{
		*exe_ret = execute(arguments, front);
		return_value = *exe_ret;
	}

	history++;

	for (i = 0; arguments[i]; i++)
		free(arguments[i]);

	return (return_value);
}
