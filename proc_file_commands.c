#include "shell.h"

int proc_file_commands(char *file_path, int *exe_ret);
int cant_open(char *file_path);

/**
 * proc_file_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **arguments, **front;
	char buffer[120];
	int ret;

	history = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, old_size, line_size);
		_stringcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size);
	arguments = _strtok(line, " ");
	free(line);
	if (!arguments)
		return (0);
	if (check_arguments(arguments) != 0)
	{
		*exe_ret = 2;
		free_arguments(arguments, arguments);
		return (*exe_ret);
	}
	front = arguments;

	for (i = 0; arguments[i]; i++)
	{
		if (_strncmp(arguments[i], ";", 1) == 0)
		{
			free(arguments[i]);
			arguments[i] = NULL;
			ret = call_arguments(arguments, front, exe_ret);
			arguments = &arguments[++i];
			i = 0;
		}
	}

	ret = call_arguments(arguments, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error, *history_string;
	int length;

	history_string = _integer_to_string(history);
	if (!history_string)
		return (127);

	length = string_length(name) + string_length(history_string) + string_length(file_path) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_string);
		return (127);
	}

	_stringcopy(error, name);
	_stringcat(error, ": ");
	_stringcat(error, history_string);
	_stringcat(error, ": Can't open ");
	_stringcat(error, file_path);
	_stringcat(error, "\n");

	free(history_string);
	write(STDERR_FILENO, error, length);
	free(error);
	return (127);
}
