#include "shell.h"

void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size);
ssize_type _getline(char **line_pointer, size_type *n, FILE *stream);
void assign_line_pointer(char **line_pointer, size_type *n, char *buffer, size_type b);

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @pointer: A pointer to the memory previously allocated.
 * @old_size: The size in bytes of the allocated space for pointer.
 * @new_size: The size in bytes for the new memory block.
 *
 * Return: If new_size == old_size - pointer.
 *         If new_size == 0 and pointer is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size)
{
	void *memory;
	char *pointer_copy, *filler;
	unsigned int index;

	if (new_size == old_size)
		return (pointer);

	if (pointer == NULL)
	{
		memory = malloc(new_size);
		if (memory == NULL)
			return (NULL);

		return (memory);
	}

	if (new_size == 0 && pointer != NULL)
	{
		free(pointer);
		return (NULL);
	}

	pointer_copy = pointer;
	memory = malloc(sizeof(*pointer_copy) * new_size);
	if (memory == NULL)
	{
		free(pointer);
		return (NULL);
	}

	filler = memory;

	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *pointer_copy++;

	free(pointer);
	return (memory);
}

/**
 * _getline - Reads input from a stream.
 * @line_pointer: A buffer to store the input.
 * @n: The size of line_pointer.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_type _getline(char **line_pointer, size_type *n, FILE *stream)
{
	static ssize_type input;
	ssize_type ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_line_pointer(line_pointer, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}

/**
 * assign_line_pointer - Reassigns the line_pointer variable for _getline.
 * @line_pointer: A buffer to store an input string.
 * @n: The size of line_pointer.
 * @buffer: The string to assign to line_pointer.
 * @b: The size of buffer.
 */
void assign_line_pointer(char **line_pointer, size_type *n, char *buffer, size_type b)
{
	if (*line_pointer == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*line_pointer = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*line_pointer = buffer;
	}
	else
	{
		_stringcopy(*line_pointer, buffer);
		free(buffer);
	}
}
