#include "shell.h"

void free_arguments(char **arguments, char **front);
void variable_replacement(char **arguments, int *exe_ret);
char *get_pid(void);
char *get_environment_value(char *beginning, int length);

/**
 * free_arguments - Frees up memory taken by arguments.
 * @arguments: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of arguments.
 */
void free_arguments(char **arguments, char **front)
{
	size_type i;

	for (i = 0; arguments[i] || arguments[i + 1]; i++)
		free(arguments[i]);

	free(front);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and environmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int j, k = 0, length;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _integer_to_string(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				length = k - (j + 1);
				replacement = get_environment_value(&old_line[j + 1], length);
			}
			new_line = malloc(j + string_length(replacement)
					  + string_length(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replacement)
			{
				_stringcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_stringcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_type i = 0;
	char *buffer;
	ssize_type file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_environment_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @length: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: variables are stored in the format variable=VALUE.
 */
char *get_environment_value(char *beginning, int length)
{
	char **variable_addr;
	char *replacement = NULL, *temp, *variable;

	variable = malloc(length + 1);
	if (!variable)
		return (NULL);
	variable[0] = '\0';
	_strncat(variable, beginning, length);

	variable_addr = _get_environment(variable);
	free(variable);
	if (variable_addr)
	{
		temp = *variable_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(string_length(temp) + 1);
		if (replacement)
			_stringcopy(replacement, temp);
	}

	return (replacement);
}
