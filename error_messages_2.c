#include "shell.h"

char *error_126(char **arguments);
char *error_127(char **arguments);

/**
 * error_126 - It creates an error message for permission denied failures.
 * @arguments: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_126(char **arguments)
{
	int length;
	char *error, *history_string;

	history_string = _integer_to_string(history);
	if (!history_string)
		return (NULL);

	length = string_length(name) + string_length(history_string) + string_length(arguments[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_string);
		return (NULL);
	}

	_stringcopy(error, name);
	_stringcat(error, ": ");
	_stringcat(error, history_string);
	_stringcat(error, ": ");
	_stringcat(error, arguments[0]);
	_stringcat(error, ": Permission denied\n");

	free(history_string);
	return (error);
}

/**
 * error_127 - It creates an error message for command not found failures.
 * @arguments: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_127(char **arguments)
{
	char *error, *history_string;
	int length;

	history_string = _integer_to_string(history);
	if (!history_string)
		return (NULL);

	length = string_length(name) + string_length(history_string) + string_length(arguments[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_string);
		return (NULL);
	}

	_stringcopy(error, name);
	_stringcat(error, ": ");
	_stringcat(error, history_string);
	_stringcat(error, ": ");
	_stringcat(error, arguments[0]);
	_stringcat(error, ": not found\n");

	free(history_string);
	return (error);
}
