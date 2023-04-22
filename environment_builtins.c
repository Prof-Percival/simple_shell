#include "shell.h"

int shell_set_environment(char **arguments, char __attribute__((__unused__)) **front);
int shell_environment(char **arguments, char __attribute__((__unused__)) **front);
int shell_unset_environment(char **arguments, char __attribute__((__unused__)) **front);

/**
 * shell_set_environment - It changes or adds an environmental variable to the PATH.
 * @arguments: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of arguments.
 * Description: arguments[1] is the name of the new or existing PATH variable.
 *              arguments[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_set_environment(char **arguments, char __attribute__((__unused__)) **front)
{
	char **environment_variable = NULL, **new_environmentment, *new_value;
	size_t size;
	int index;

	if (!arguments[0] || !arguments[1])
		return (create_an_error(arguments, -1));

	new_value = malloc(string_length(arguments[0]) + 1 + string_length(arguments[1]) + 1);
	if (!new_value)
		return (create_an_error(arguments, -1));
	_stringcopy(new_value, arguments[0]);
	_stringcat(new_value, "=");
	_stringcat(new_value, arguments[1]);

	environment_variable = _get_environment(arguments[0]);
	if (environment_variable)
	{
		free(*environment_variable);
		*environment_variable = new_value;
		return (0);
	}
	for (size = 0; environment[size]; size++)
		;

	new_environmentment = malloc(sizeof(char *) * (size + 2));
	if (!new_environmentment)
	{
		free(new_value);
		return (create_an_error(arguments, -1));
	}

	for (index = 0; environment[index]; index++)
		new_environmentment[index] = environment[index];

	free(environment);
	environment = new_environmentment;
	environment[index] = new_value;
	environment[index + 1] = NULL;

	return (0);
}

/**
 * shell_environment - It prints the current environment.
 * @arguments: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of arguments.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: It prints one variable per line in the
 *              format 'variable'='value'.
 */
int shell_environment(char **arguments, char __attribute__((__unused__)) **front)
{
	int index;
	char newline_character = '\n';

	if (!environment)
		return (-1);

	for (index = 0; environment[index]; index++)
	{
		write(STDOUT_FILENO, environment[index], string_length(environment[index]));
		write(STDOUT_FILENO, &newline_character, 1);
	}

	(void)arguments;
	return (0);
}

/**
 * shell_unset_environment - Deletes an environmental variable from the PATH.
 * @arguments: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of arguments.
 * Description: arguments[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_unset_environment(char **arguments, char __attribute__((__unused__)) **front)
{
	size_t size;
	char **environment_variable, **new_environmentment;
	int index, index2;

	if (!arguments[0])
		return (create_an_error(arguments, -1));
	environment_variable = _get_environment(arguments[0]);
	if (!environment_variable)
		return (0);

	for (size = 0; environment[size]; size++)
		;

	new_environmentment = malloc(sizeof(char *) * size);
	if (!new_environmentment)
		return (create_an_error(arguments, -1));

	for (index = 0, index2 = 0; environment[index]; index++)
	{
		if (*environment_variable == environment[index])
		{
			free(*environment_variable);
			continue;
		}
		new_environmentment[index2] = environment[index];
		index2++;
	}
	free(environment);
	environment = new_environmentment;
	environment[size - 1] = NULL;

	return (0);
}
