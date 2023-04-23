#include "shell.h"

char **_copy_environment(void);
void free_environment(void);
char **_get_environment(const char *variable);

/**
 * _copy_environment - It creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copy_environment(void)
{
	char **new_environment;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environment = malloc(sizeof(char *) * (size + 1));
	if (!new_environment)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environment[index] = malloc(string_length(environ[index]) + 1);

		if (!new_environment[index])
		{
			for (index--; index >= 0; index--)
				free(new_environment[index]);
			free(new_environment);
			return (NULL);
		}
		_stringcopy(new_environment[index], environ[index]);
	}
	new_environment[index] = NULL;

	return (new_environment);
}

/**
 * free_environment - Frees the the environ copy.
 */
void free_environment(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}


/**
 * _get_environment - Gets an environmental variable from the PATH.
 * @variable: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_get_environment(const char *variable)
{
	int index, length;

	length = string_length(variable);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(variable, environ[index], length) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
