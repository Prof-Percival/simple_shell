#include "shell.h"

int string_length(const char *s);
char *_stringcat(char *destination, const char *source);
char *_stringcopy(char *destination, const char *source);
char *_strncat(char *destination, const char *source, size_t n);

/**
 * string_length - Returns the length of a string.
 * @s: A pointer to the characters string.
 *
 * Return: The length of the character string.
 */
int string_length(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}

/**
 * _stringcat - Concantenates two strings.
 * @destination: Pointer to destination string.
 * @source: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *_stringcat(char *destination, const char *source)
{
	const char *srcTemp;
	char *destTemp;

	destTemp = destination;
	srcTemp =  source;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (destination);
}

/**
 * _stringcopy - Copies the string pointed to by source, including the
 *           terminating null byte, to the buffer pointed by des.
 * @destination: Pointer to the destination of copied string.
 * @source: Pointer to the source of the source string.
 *
 * Return: Pointer to destination.
 */
char *_stringcopy(char *destination, const char *source)
{
	size_t i;

	for (i = 0; source[i] != '\0'; i++)
		destination[i] = source[i];
	destination[i] = '\0';
	return (destination);
}


/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @destination: Pointer to destination string.
 * @source: Pointer to source string.
 * @n: n bytes to copy from source.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *destination, const char *source, size_t n)
{
	size_t dest_length = string_length(destination);
	size_t i;

	for (i = 0; i < n && source[i] != '\0'; i++)
		destination[dest_length + i] = source[i];
	destination[dest_length + i] = '\0';

	return (destination);
}
