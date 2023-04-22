#include "shell.h"

int count_tokens(char *str, char *delim);
int token_length(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * count_tokens - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, length = 0;

	for (index = 0; *(str + index); index++)
		length++;

	for (index = 0; index < length; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_length(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * token_length - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int token_length(char *str, char *delim)
{
	int index = 0, length = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		length++;
		index++;
	}

	return (length);
}

/**
 * _strtok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *delim)
{
	char **pointer;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	pointer = malloc(sizeof(char *) * (tokens + 2));
	if (!pointer)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_length(line + index, delim);

		pointer[t] = malloc(sizeof(char) * (letters + 1));
		if (!pointer[t])
		{
			for (index -= 1; index >= 0; index--)
				free(pointer[index]);
			free(pointer);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			pointer[t][l] = line[index];
			index++;
		}

		pointer[t][l] = '\0';
	}
	pointer[t] = NULL;
	pointer[t + 1] = NULL;

	return (pointer);
}
