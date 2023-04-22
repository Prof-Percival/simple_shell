#include "shell.h"

int number_length(int number);
int create_an_error(char **arguments, int error_value);
char *_integer_to_string(int number);

/**
 * number_length - It counts the digit length of a number.
 * @number: The number to measure.
 *
 * Return: The digit length.
 */
int number_length(int number)
{
	int length = 1;
	unsigned int number1;

	if (number < 0)
	{
		length++;
		number1 = number * -1;
	}
	else
	{
		number1 = number;
	}
	while (number1 > 9)
	{
		length++;
		number1 /= 10;
	}

	return (length);
}

/**
 * create_an_error - It writes a custom error message to stderror.
 * @arguments: An array of arguments.
 * @error: The error value.
 *
 * Return: The error value.
 */
int create_an_error(char **arguments, int error_value)
{
	char *error;

	switch (error_value)
	{
	case -1:
		error = error_environment(arguments);
		break;
	case 1:
		error = error_1(arguments);
		break;
	case 2:
		if (*(arguments[0]) == 'e')
			error = error_2_exit(++arguments);
		else if (arguments[0][0] == ';' || arguments[0][0] == '&' || arguments[0][0] == '|')
			error = error_2_syntax(arguments);
		else
			error = error_2_change_directory(arguments);
		break;
	case 126:
		error = error_126(arguments);
		break;
	case 127:
		error = error_127(arguments);
		break;
	}
	write(STDERR_FILENO, error, string_length(error));

	if (error)
		free(error);
	return (error_value);

}

/**
 * _integer_to_string - It converts an integer to a string.
 * @number: The integer.
 *
 * Return: The converted string.
 */
char *_integer_to_string(int number)
{
	int length = number_length(number);
	char *buffer;
	unsigned int number1;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);

	buffer[length] = '\0';

	if (number < 0)
	{
		number1 = number * -1;
		buffer[0] = '-';
	}
	else
	{
		number1 = number;
	}

	length--;
	do {
		buffer[length] = (number1 % 10) + '0';
		number1 /= 10;
		length--;
	} while (number1 > 0);

	return (buffer);
}
