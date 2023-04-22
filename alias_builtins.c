#include "shell.h"

int shell_alias(char **arguments, char __attribute__((__unused__)) **front);
void set_an_alias(char *alias_name, char *value);
void print_the_alias(alias_type *alias);

/**
 * shell_alias - Builtin command that either prints all, specific or sets an alias.
 * @arguments: An array of arguments.
 * @front: A double pointer to the beginning of arguments.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_alias(char **arguments, char __attribute__((__unused__)) **front)
{
	int i, value_to_return = 0;
	alias_type *temp_value = aliases;
	char *value;

	if (!arguments[0])
	{
		while (temp_value)
		{
			print_the_alias(temp_value);
			temp_value = temp_value->next;
		}
		return (value_to_return);
	}
	for (i = 0; arguments[i]; i++)
	{
		temp_value = aliases;
		value = _strchr(arguments[i], '=');
		if (!value)
		{
			while (temp_value)
			{
				if (_string_compare(arguments[i], temp_value->name) == 0)
				{
					print_the_alias(temp_value);
					break;
				}
				temp_value = temp_value->next;
			}
			if (!temp_value)
				value_to_return = create_an_error(arguments + i, 1);
		}
		else
			set_an_alias(arguments[i], value);
	}
	return (value_to_return);
}

/**
 * set_an_alias - Will either set an existing alias 'name' with a new value,
 * or It creates a new alias with the 'name' and 'value'.
 * @alias_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void set_an_alias(char *alias_name, char *value)
{
	int k, j, length;
	alias_type *temp_value = aliases;
	char *new_value;

	*value = '\0';
	value++;
	length = string_length(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (length + 1));
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
		if (_string_compare(alias_name, temp_value->name) == 0)
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
void print_the_alias(alias_type *alias)
{
	char *alias_shelltring;
	int length = string_length(alias->name) + string_length(alias->value) + 4;

	alias_shelltring = malloc(sizeof(char) * (length + 1));
	if (!alias_shelltring)
		return;
	_stringcopy(alias_shelltring, alias->name);
	_stringcat(alias_shelltring, "='");
	_stringcat(alias_shelltring, alias->value);
	_stringcat(alias_shelltring, "'\n");

	write(STDOUT_FILENO, alias_shelltring, length);
	free(alias_shelltring);
}
/**
 * replace_aliases - It goes through the arguments and then replace any matching alias
 * with their value.
 * @arguments: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **arguments)
{
	alias_type *temp_value;
	int i;
	char *new_value;

	if (_string_compare(arguments[0], "alias") == 0)
		return (arguments);
	for (i = 0; arguments[i]; i++)
	{
		temp_value = aliases;
		while (temp_value)
		{
			if (_string_compare(arguments[i], temp_value->name) == 0)
			{
				new_value = malloc(sizeof(char) * (string_length(temp_value->value) + 1));
				if (!new_value)
				{
					free_arguments(arguments, arguments);
					return (NULL);
				}
				_stringcopy(new_value, temp_value->value);
				free(arguments[i]);
				arguments[i] = new_value;
				i--;
				break;
			}
			temp_value = temp_value->next;
		}
	}

	return (arguments);
}
