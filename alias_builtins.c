#include "shell.h"

int alias_builtin(char **args, char __attribute__((__unused__)) **front);
void set_an_alias(char *alias_name, char *value);
void print_the_alias(alias_t *alias);

/**
 * alias_builtin - Builtin command that either prints all, specific or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int alias_builtin(char **args, char __attribute__((__unused__)) **front)
{
	int i, value_to_return = 0;
	alias_t *temp_value = aliases;
	char *value;

	if (!args[0])
	{
		while (temp_value)
		{
			print_the_alias(temp_value);
			temp_value = temp_value->next;
		}
		return (value_to_return);
	}
	for (i = 0; args[i]; i++)
	{
		temp_value = aliases;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (temp_value)
			{
				if (_strcmp(args[i], temp_value->name) == 0)
				{
					print_the_alias(temp_value);
					break;
				}
				temp_value = temp_value->next;
			}
			if (!temp_value)
				value_to_return = create_an_error(args + i, 1);
		}
		else
			set_an_alias(args[i], value);
	}
	return (value_to_return);
}

/**
 * set_an_alias - Will either set an existing alias 'name' with a new value,
 * or creates a new alias with the 'name' and 'value'.
 * @alias_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void set_an_alias(char *alias_name, char *value)
{
	int k, j, len;
	alias_t *temp_value = aliases;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp_value)
	{
		if (_strcmp(alias_name, temp_value->name) == 0)
		{
			free(temp_value->value);
			temp_value->value = new_value;
			break;
		}
		temp_value = temp_value->next;
	}
	if (!temp_value)
		add_alias_end(&aliases, alias_name, new_value);
}

/**
 * print_the_alias - Prints the alias in the format of name='value'.
 * @alias: Pointer to an alias.
 */
void print_the_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * replace_aliases - It goes through the arguments and then replace any matching alias
 * with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *temp_value;
	int i;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp_value = aliases;
		while (temp_value)
		{
			if (_strcmp(args[i], temp_value->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp_value->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp_value->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			temp_value = temp_value->next;
		}
	}

	return (args);
}
