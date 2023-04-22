#include "shell.h"

char *_strchr(char *s, char c);
int _string_compare(char *string1, char *string2);
int _strspn(char *s, char *accept);
int _strncmp(const char *string1, const char *string2, size_type n);

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to be located.
 *
 * Return: If c is found - a pointer to the first occurence.
 *         If c is not found - NULL.
 */
char *_strchr(char *s, char c)
{
	int index;

	for (index = 0; s[index]; index++)
	{
		if (s[index] == c)
			return (s + index);
	}

	return (NULL);
}

/**
 * _string_compare - Compares two strings.
 * @string1: The first string to be compared.
 * @string2: The second string to be compared.
 *
 * Return: Positive byte difference if string1 > string2
 *         0 if string1 = string2
 *         Negative byte difference if string1 < string2
 */
int _string_compare(char *string1, char *string2)
{
	while (*string1 && *string2 && *string1 == *string2)
	{
		string1++;
		string2++;
	}

	if (*string1 != *string2)
		return (*string1 - *string2);

	return (0);
}

/**
 * _strspn - Gets the length of a prefix substring.
 * @s: The string to be searched.
 * @accept: The prefix to be measured.
 *
 * Return: The number of bytes in s which
 *         consist only of bytes from accept.
 */
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}


/**
 * _strncmp - Compare two strings.
 * @string1: Pointer to a string.
 * @string2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 *
 * Return: Less than 0 if string1 is shorter than string2.
 *         0 if string1 and string2 match.
 *         Greater than 0 if string1 is longer than string2.
 */
int _strncmp(const char *string1, const char *string2, size_type n)
{
	size_type i;

	for (i = 0; string1[i] && string2[i] && i < n; i++)
	{
		if (string1[i] > string2[i])
			return (string1[i] - string2[i]);
		else if (string1[i] < string2[i])
			return (string1[i] - string2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
