#include "shell.h"

char *error_environment(char **arguments);
char *error_1(char **arguments);
char *error_2_exit(char **arguments);
char *error_2_change_directory(char **arguments);
char *error_2_syntax(char **arguments);
/**
 * error_environment - It creates an error message for shell_environment errors.
 * @arguments: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_environment(char **arguments)
{
	char *error, *history_string;
	int length;

	history_string = _integer_to_string(history);
	if (!history_string)
		return (NULL);

	arguments--;
	length = string_length(name) + string_length(history_string) + string_length(arguments[0]) + 45;
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
	_stringcat(error, ": Unable to add/remove from environment\n");

	free(history_string);
	return (error);
}

/**
 * error_1 - It creates an error message for shell_alias errors.
 * @arguments: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **arguments)
{
	char *error;
	int length;

	length = string_length(name) + string_length(arguments[0]) + 13;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
		return (NULL);

	_stringcopy(error, "alias: ");
	_stringcat(error, arguments[0]);
	_stringcat(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - It creates an error message for shell_exit errors.
 * @arguments: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_exit(char **arguments)
{
	char *error, *history_string;
	int length;

	history_string = _integer_to_string(history);
	if (!history_string)
		return (NULL);

	length = string_length(name) + string_length(history_string) + string_length(arguments[0]) + 27;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_string);
		return (NULL);
	}

	_stringcopy(error, name);
	_stringcat(error, ": ");
	_stringcat(error, history_string);
	_stringcat(error, ": exit: Illegal number: ");
	_stringcat(error, arguments[0]);
	_stringcat(error, "\n");

	free(history_string);
	return (error);
}

/**
 * error_2_change_directory - It creates an error message for shell_change directory errors.
 * @arguments: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_change_directory(char **arguments)
{
	char *error, *history_string;
	int length;

	history_string = _integer_to_string(history);
	if (!history_string)
		return (NULL);

	if (arguments[0][0] == '-')
		arguments[0][2] = '\0';
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
	if (arguments[0][0] == '-')
		_stringcat(error, ": cd: Illegal option ");
	else
		_stringcat(error, ": cd: can't cd to ");
	_stringcat(error, arguments[0]);
	_stringcat(error, "\n");

	free(history_string);
	return (error);
}

/**
 * error_2_syntax - It creates an error message for syntax errors.
 * @arguments: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **arguments)
{
	char *error, *history_string;
	int length;

	history_string = _integer_to_string(history);
	if (!history_string)
		return (NULL);

	length = string_length(name) + string_length(history_string) + string_length(arguments[0]) + 33;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_string);
		return (NULL);
	}

	_stringcopy(error, name);
	_stringcat(error, ": ");
	_stringcat(error, history_string);
	_stringcat(error, ": Syntax error: \"");
	_stringcat(error, arguments[0]);
	_stringcat(error, "\" unexpected\n");

	free(history_string);
	return (error);
}
