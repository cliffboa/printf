#include "main.h"

/**
 * print_buffer - Prints the contents of the buffer if it exists.
 * @buffer: Array of characters representing the buffer.
 * @buff_ind: Pointer to an integer representing the index to add the next character.
 *
 * This function prints the contents of the buffer to the standard output if it is not empty.
 * The buffer is a character array that temporarily stores characters before printing them
 * to avoid multiple write system calls for small chunks of data.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

/**
 * _printf - Custom printf function.
 * @format: Formatted string containing the format and arguments.
 *
 * This function implements a custom version of the printf function that supports
 * various format specifiers and conversion flags. It processes the format string and
 * handles the printing of different data types according to the provided format.
 *
 * Return: The number of characters printed on success, or -1 if an error occurs.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);

			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
			                       flags, width, precision, size);

			if (printed == -1)
				return (-1);

			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);
	va_end(list);

	return (printed_chars);
}

