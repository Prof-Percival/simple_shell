#include "shell.h"

list_type *add_node_end(list_type **head, char *dir);
alias_type *add_alias_end(alias_type **head, char *name, char *value);
void free_list(list_type *head);
void free_alias_list(alias_type *head);

/**
 * add_node_end - Adds a node to the end of a list_type linked list.
 * @head: A pointer to the head of the list_type list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_type *add_node_end(list_type **head, char *dir)
{
	list_type *new_node = malloc(sizeof(list_type));
	list_type *last;

	if (!new_node)
		return (NULL);

	new_node->directory = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * add_alias_end - Adds a node to the end of a alias_type linked list.
 * @head: A pointer to the head of the list_type list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alias_type *add_alias_end(alias_type **head, char *name, char *value)
{
	alias_type *new_node = malloc(sizeof(alias_type));
	alias_type *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (string_length(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_stringcopy(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * free_list - Frees a list_type linked list.
 * @head: The head of the list_type list.
 */
void free_list(list_type *head)
{
	list_type *next;

	while (head)
	{
		next = head->next;
		free(head->directory);
		free(head);
		head = next;
	}
}

/**
 * free_alias_list - Frees a alias_type linked list.
 * @head: THe head of the alias_type list.
 */
void free_alias_list(alias_type *head)
{
	alias_type *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}
